#include <iostream>
#include <vector>
using namespace std;

bool check(vector<vector<pair<int, int>>> &cache, int tar)
{
    for (int i = 0; i < cache.size(); ++i)
        for (int j = 0; j < cache[i].size(); ++j)
        {
            // pair<int, int> cur = cache[i][j];
            if (cache[i][j].first == tar)
            {
                cache[i][j].second++;
                return true;
            }
        }

    return false;
}

int place(const vector<pair<int, int>> &cache_set)
{
    for (int i = 0; i < cache_set.size(); ++i)
        if (cache_set[i] == pair(-1, -1))
            return i;

    int freq = cache_set[0].second,
        ind = 0;

    for (int i = 0; i < cache_set.size(); ++i)
    {
        pair<int, int> cur = cache_set[i];

        if (cur.second < freq)
        {
            freq = cur.second;
            ind = i;
        }
    }

    return ind;
}

int main()
{
    int cacheBlocks, k, n;
    cin >> cacheBlocks >> k >> n;

    vector<int> arr(n, -1);
    for (int i = 0; i < arr.size(); ++i)
        cin >> arr[i];

    int cnt = 0;
    vector<vector<pair<int, int>>> cache(cacheBlocks / k, vector(k, pair(-1, -1)));
    for (int i = 0; i < arr.size(); ++i)
    {
        if (check(cache, arr[i]) == false)
        {
            int set = i % cache.size(),
                ind = place(cache[set]);

            cache[set][ind] = {arr[i], 1};

            cnt++;
        }

        // cout << "i:" << i << "\n";
        // for (auto it : cache)
        // {
        //     for (auto k : it)
        //         cout << k.first << " " << k.second << "\n";
        //     cout << "\n";
        // }
        // cout << "cnt:" << cnt << "\n\n";
    }

    cout << "Total Cache Misses:" << cnt << endl;
    return 0;
}