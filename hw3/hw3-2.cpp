#include <chrono>
#include <iostream>
#include <mutex>
#include <random>
#include <semaphore.h>
#include <thread>
#include <vector>

using namespace std;

constexpr int MAX_VERTICES = 750;
constexpr ptrdiff_t MAX_THREADS{4};

mutex mutexes[MAX_VERTICES];
counting_semaphore semaphores{MAX_THREADS};

// random number generator
random_device dev;
mt19937 rng(dev());
uniform_int_distribution<mt19937::result_type> dist(1, 10);

// num of vertices & num of edges
int V, E;
vector<int> adjacent_matrix[MAX_VERTICES];

// vertex_check[i]:
//    0: not checked
//    1: checked
bool vertex_checked[MAX_VERTICES];

// vertex_status[i]:
//    0: not in independent set
//    1: in independent set
bool vertex_status[MAX_VERTICES];

// if every vertex is checked, then the graph is converged
bool is_converged()
{
  for (int i = 0; i < V; i++)
    if (!vertex_checked[i])
      return false;
  return true;
}

// if any neighbor is in the set, then leave the set
bool best_response(int v)
{
  for (int u : adjacent_matrix[v])
    if (vertex_status[u])
      return false;
  return true;
}

sem_t s;

void maximum_independent_set(int v)
{
  // sem_wait(&s);

  bool converged = false;

  while (!converged)
  {
    if (vertex_checked[v])
    {
      sem_wait(&s);
      converged = is_converged();
      sem_post(&s);
    }
    else
    {
      sem_wait(&s);
      bool old_response = vertex_status[v];
      vertex_status[v] = best_response(v);
      // sem_post(&s);

      // sem_wait(&s);
      vertex_checked[v] = true;
      if (vertex_status[v] != old_response)
      {
        for (int u : adjacent_matrix[v])
          vertex_checked[u] = false;
      }
      sem_post(&s);
    }
  }

  // sem_post(&s);
}

int main(void)
{
  int res = sem_init(&s, 0, 1);

  cin >> V >> E;

  thread t[V];

  for (int i = 0; i < V; i++)
  {
    vertex_checked[i] = false;
    vertex_status[i] = false;
  }

  for (int i = 0; i < E; i++)
  {
    int u, v;
    cin >> u >> v;
    adjacent_matrix[v].push_back(u);
    adjacent_matrix[u].push_back(v);
  }

  for (int i = 0; i < V; i++)
    t[i] = thread(maximum_independent_set, i);

  for (int i = 0; i < V; i++)
    t[i].join();

  for (int i = 0; i < V; i++)
  {
    if (!vertex_status[i])
      continue;
    cout << i << ' ';
    // cout<<"0 ";
  }
  cout << '\n';
}
