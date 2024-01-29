#include <iostream>
#include <vector>
using namespace std;

int check(const vector<int> &cache, const int tar)
{
    int exist = -1;

    for (int i = 0; i < cache.size(); ++i)
        if (cache[i] == tar)
        {
            exist = i;
            break;
        }

    return exist;
}

int main()
{
    int cacheBlock = 0,
        inputNumber = 0;

    cin >> cacheBlock >> inputNumber;

    vector<int> arr(inputNumber, -1);
    for (int i = 0; i < inputNumber; ++i)
        cin >> arr[i];

    vector<int> cache(cacheBlock, -1);
    int cnt = 0;
    for (int i = 0; i < arr.size(); ++i)
    {
        if (check(cache, arr[i]) == -1)
        {
            cache[i % cache.size()] = arr[i];
            cnt++;
        }
    }

    cout << "Total Cache Misses:" << cnt << endl;
}