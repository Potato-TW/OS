#include <iostream>
#include <vector>
using namespace std;

bool check(vector<vector<pair<int, int>>> &cache, const int tar, const int ind)
{
    bool exist = false;

    for (int i = 0; i < cache.size(); ++i)
    {
        for (int j = 0; j < cache[i].size(); ++j)
        {
            if (cache[i][j].first == tar)
            {
                cache[i][j].second = 0;
                exist = true;

                return exist;
            }
        }
    }

    return exist;
}

int place(const vector<pair<int, int>> &cache_set)
{
    for (int i = 0; i < cache_set.size(); ++i)
        if (cache_set[i] == pair(-1, -1))
            return i;

    int ind = 0,
        recent = cache_set[0].second;

    for (int j = 0; j < cache_set.size(); ++j)
    {
        pair<int, int> cur = cache_set[j];

        if (cur.second > recent)
        {
            recent = cur.second;
            ind = j;
        }
    }

    return ind;
}

int main()
{
    int cacheBlocks, k, n;
    cin >> cacheBlocks >> k >> n;

    vector<int> arr(n, -1);
    for (int i = 0; i < n; ++i)
        cin >> arr[i];

    int cnt = 0;
    vector<vector<pair<int, int>>> cache(cacheBlocks / k, vector(k, pair(-1, -1)));
    for (int i = 0; i < arr.size(); ++i)
    {
        if (check(cache, arr[i], i) == false)
        {
            int set = i % cache.size(),
                ind = place(cache[set]);

            cache[set][ind] = {arr[i], 0};
            cnt++;

            // cout << "cnt:" << cnt << "\n";
        }

        for (int j = 0; j < cache.size(); ++j)
            for (int k = 0; k < cache[j].size(); ++k)
                if (cache[j][k] != pair(-1, -1))
                    cache[j][k].second++;

        // cout << "i:" << i << "\n";
        // for (auto i : cache)
        // {
        //     for (auto j : i)
        //         cout << j.first << " " << j.second << "\n";
        //     cout << "\n";
        // }
    }

    cout << "Total Cache Misses:" << cnt << endl;
    return 0;
}