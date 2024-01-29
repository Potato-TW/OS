#include <iostream>
#include <cstdint>
#include <vector>
#include <thread>
#include <semaphore.h>
#include <future>
#include <cmath>

using namespace std;

int n, m;
vector<uint64_t> subsets;
uint64_t one = static_cast<uint64_t>(1), global_count = 0;

// uint64_t res[4];
vector<uint64_t> res;

sem_t s;
int cnt = 0;

int numth = 0;

void solve_init(int index, uint64_t current)
{
    if (index == log2(numth) && res.size() < numth)
    {
        res.push_back(current);
        return;
    }

    if (index == m)
    {
        if (current == (one << n) - 1)
            global_count++;
    }
    else
    {
        solve_init(index + 1, current);
        solve_init(index + 1, current | subsets[index]);
    }
}

int solve(int index, uint64_t current)
{

    // cout << "ind: " << index << " cur: " << current << " tid: " << thread_id << "\n";
    if (index == m)
    {
        if (current == (one << n) - 1)
        {
            return 1;
            // sem_wait(&s);
            // global_count++;
            // sem_post(&s);
        }
        else
            return 0;
    }
    else
    {
        return solve(index + 1, current) + solve(index + 1, current | subsets[index]);
    }
}

void why(uint64_t cur, promise<uint64_t> &&p /*,future<uint64_t> &f*/)
{
    p.set_value(solve(log2(numth), cur));
    // global_count+= f.get();
    // return ;
}

int main(int argc, char *argv[])
{
    numth = atoi(argv[2]);

    sem_init(&s, 0, 1);
    cin >> n >> m;

    subsets.resize(m);
    for (int i = 0; i < m; i++)
    {
        int p, temp;
        cin >> p;
        for (int j = 0; j < p; j++)
        {
            cin >> temp;
            subsets[i] |= (one << temp);
        }
    }
    
    solve_init(0, 0);

    if (!res.empty())
    {
        vector<thread> t;
        // t.resize(4);
        vector<promise<uint64_t>> p;
        p.resize(numth);
        vector<future<uint64_t>> f;
        f.resize(numth);

        for (int i = 0; i < numth; ++i)
        {
            f[i] = p[i].get_future();
            t.emplace_back(why, res[i], move(p[i]));
        }

        for (int i = 0; i < numth; ++i)
        {
            t[i].join();
            global_count += f[i].get();
        }
    }

    cout << global_count << endl;
    return 0;
}
