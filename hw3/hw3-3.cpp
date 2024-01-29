#include <iostream>
#include <thread>
#include <cstring>
#include <semaphore.h>
#include <mutex>
#include <vector>

using namespace std;

int n, global_count = 0;

bool is_prime(int num)
{
    if (num == 1)
        return false;

    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}

sem_t s;
mutex m;

int numth = 0;

void func(int k)
{
    int low = n / numth * k;
    int upp = n / numth * (k + 1);
    if (k == numth - 1)
        upp = n;

    for (int i = low + 1; i <= upp; ++i)
        if (is_prime(i))
        {
            sem_wait(&s);
            global_count++;
            sem_post(&s);
        }
}

int main(int argc, char *argv[])
{
    numth = atoi(argv[2]);
    // cout << "argv " << numth << "\n";
    sem_init(&s, 0, 1);

    cin >> n;

    vector<thread> t;
    t.resize(numth);
    for (int i = 0; i < t.size(); ++i)
    {
        t[i] = thread(func, i);
    }

    for (int i = 0; i < t.size(); ++i)
    {
        t[i].join();
    }

    cout << global_count << endl;

    return 0;
}
