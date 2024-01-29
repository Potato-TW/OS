#include <bits/stdc++.h>

#define pii pair<int, int>
using namespace std;

vector<vector<int>> fcfs(vector<vector<int>> data, vector<vector<int>> &res, bool last)
{
    // vector<vector<int>> res;
    // cout << "\nfcfs\n";
    vector<vector<int>> nextLevel;

    int sum = 0;
    for (int i = 0; i < data.size(); ++i)
    {
        // vector<int> tmp(2, 0);

        int arr = data[i][1],
            burst = data[i][2];

        if (sum >= arr)
            res[i][0] = sum - arr;
        else
        {
            res[i][0] = 0;
            sum = arr;
        }
        res[i][1] = res[i][0] + burst;

        sum += burst;

        // res.push_back(tmp);
    }

    // vector<int> tmp(2, 0);
    int totalw = 0, totalb = 0;
    for (int i = 0; i < res.size(); ++i)
    {
        totalw += res[i][0];
        totalb += res[i][1];
    }
    res.push_back({totalw, totalb});

    return nextLevel;
}

bool srtfcmp(vector<int> &a, vector<int> &b)
{
    if (a[1] < b[1])
        return 1;
    else if (a[1] > b[1])
        return 0;
    else
    {
        if (a[2] == b[2])
            return a[0] < b[0];
        else
            return a[2] < b[2];        
    }
    
    return -1;
}

vector<vector<int>> srtf(vector<vector<int>> data, vector<vector<int>> &res, bool last)
{
    // cout << "\nsrtf\n";

    vector<vector<int>> nextLevel;
    while (!data.empty())
    {
        sort(data.begin(), data.end(), srtfcmp);

        int &curNum = data[0][0],
            &curArr = data[0][1],
            &curBurst = data[0][2],
            &nextArr = data[1][1],
            &nextBurst = data[1][2];

        int maxB = curBurst + curArr,
            index = data.size();
        for (int i = 0; i < data.size(); ++i)
        {
            if (data[i][1] != data[0][1])
            {
                maxB = data[i][1];
                index = i;
                break;
            }
        }

        int diff = 0;
        if (maxB >= curBurst + curArr)
            diff = curBurst;
        else
            diff = maxB - curArr;

        for (int i = 0; i < index; ++i)
        {
            data[i][1] += diff;
        }

        curBurst -= diff;

        if (data[0][2] == 0)
        {
            int num = data[0][0];
            res[num][0] += data[0][1];
            data.erase(data.begin());
            continue;
        }
    }

    int totalw = 0, totalb = 0;
    for (int i = 0; i < res.size(); ++i)
    {
        res[i][1] += res[i][0];
        totalw += res[i][0];
        totalb += res[i][1];
    }
    res.push_back({totalw, totalb});

    return nextLevel;
}

vector<vector<int>> rr(vector<vector<int>> data, int timeQ, vector<vector<int>> &res, bool last)
{
    // cout << "\nRR\n";
    vector<vector<int>> nextLevel;
    vector<vector<int>> queue = {data[0]};
    int cur = data[0][1];
    int ind = 1;
    while (!queue.empty() || ind < data.size())
    {
        int dif = queue[0][2];
        if (dif > timeQ)
            dif = timeQ;

        if (ind < data.size())
        {
            while (cur + dif >= data[ind][1])
            {
                queue.push_back(data[ind]);
                ind++;

                if (ind >= data.size())
                    break;
            }
        }

        vector<int> tmp = queue[0];
        int diff = 0;
        if (tmp[2] > timeQ)
            diff = timeQ;
        else
            diff = tmp[2];

        queue[0][2] -= diff;
        cur += diff;

        if (queue[0][2] != 0)
        {

            queue.push_back(queue[0]);
            queue.erase(queue.begin());
        }
        else
        {
            int num = queue[0][0];
            res[num][0] += cur;

            queue.erase(queue.begin());

            if (queue.empty() && ind < data.size())
            {
                queue.push_back(data[ind]);
                ind++;
                cur = queue[0][1];
            }
        }
    }

    int totalw = 0, totalb = 0;
    for (int i = 0; i < res.size(); ++i)
    {
        totalw += res[i][0];
        res[i][1] += res[i][0];
        totalb += res[i][1];
    }

    res.push_back({totalw, totalb});

    return nextLevel;
}

void show(vector<vector<int>> ans)
{
    for (int i = 0; i < ans.size() - 1; ++i)
    {
        // for (int j = 0; j < ans[i].size(); ++j)
        // {
        //     cout << ans[i][j] << " ";
        // }
        // cout << "\n";

        cout << ans[i][0] << " " << ans[i][1] << "\n";
    }
    cout << ans[ans.size() - 1][0] << "\n"
         << ans[ans.size() - 1][1] << "\n";
}

vector<vector<int>> multi_fcfs(vector<vector<int>> data, vector<vector<int>> &res, map<int, int> &map, bool last);
vector<vector<int>> multi_srtf(vector<vector<int>> data, vector<vector<int>> &res, map<int, int> &map, bool last);
vector<vector<int>> multi_rr(vector<vector<int>> data, vector<vector<int>> &res, map<int, int> &map, bool last, int timeQ);
int cc = 0;
int main()
{
    int n, m;
    cin >> n >> m;

    vector<vector<int>> level;
    for (int i = 0; i < n; ++i)
    {
        int mode, timeQ;
        cin >> mode >> timeQ;
        level.push_back({mode, timeQ});
    }

    vector<vector<int>> arr;
    for (int i = 0; i < m; ++i)
    {
        int a, b;
        cin >> a >> b;
        arr.push_back({i, a, b});
    }

    vector<vector<int>> res(arr.size(), vector<int>(2, 0));
    for (int i = 0; i < arr.size(); ++i)
    {
        res[i][1] = arr[i][2];
        res[i][0] = -arr[i][1] - arr[i][2];
    }

    bool last = 0;

    if (level.size() == 1)
        if (level[0][0] == 0)
        {
            // map<int, int>map;
            // map.insert({0,INT_MAX});
            arr = fcfs(arr, res, last);
            // arr=multi_fcfs(arr,res,map,1);
            show(res);
        }
        else if (level[0][0] == 1)
        {
            // map<int, int> map;
            // map[0] = INT_MAX;
            arr = srtf(arr, res, last);
            // arr = multi_srtf(arr, res, map, 1);

            show(res);
        }
        else
        {

            arr = rr(arr, level[0][1], res, last);
            // arr = multi_rr(arr, res, map, 1, level[0][1]);

            show(res);
        }
    else
    {
        map<int, int> map;
        map.insert({0, INT_MAX});
        // map.insert({0, 5});
        // map.insert({5, 10});
        // map.insert({21, INT_MAX});

        int queuetime = 0;
        for (int i = 0; i < level.size(); ++i)
        {
            // cout << "arr.size = " << arr.size() << "\n";
            if (arr.empty())
                break;

            // cout << "i: " << i << "\n";
            int mode = level[i][0], timeQ = level[i][1];
            if (mode == 0)
                arr = multi_fcfs(arr, res, map, (i == level.size() - 1));
            else if (mode == 1)
                arr = multi_srtf(arr, res, map, (i == level.size() - 1));
            else
                arr = multi_rr(arr, res, map, (i == level.size() - 1), timeQ);

            // cout << "---------------\narr:\n";
            // for (auto i : arr)
            // {
            //     for (auto j : i)
            //     {
            //         cout << j << " ";
            //     }
            //     cout << "\n";
            // }
            // cout << "----------------\nmap:\n";
            // for (auto i : map)
            // {
            //     cout << i.first << " " << i.second << "\n";
            // }
            // cout << "\n";
            // cout << "=============\n";
        }

        // cout << "---------\ncal:\n";

        // cout << "ans:\n";
        int totalw = 0, totalb = 0;
        for (int i = 0; i < res.size(); ++i)
        {
            // for (int j = 0; j < res[i].size(); ++j)
            // {
            //     if (j == 0)
            //     {
            //         totalw += res[i][j];
            //     }
            //     else
            //     {
            //         res[i][j] += res[i][j - 1];
            //         totalb += res[i][j];
            //     }
            //     cout << res[i][j] << " ";
            // }
            res[i][1] += res[i][0];
            totalw += res[i][0];
            totalb += res[i][1];

            cout << res[i][0] << " " << res[i][1];
            cout << "\n";
        }
        cout << totalw << "\n"
             << totalb << "\n";
    }

    // cout << "cc: " << cc << "\n";

    return 0;
}

vector<vector<int>> multi_fcfs(vector<vector<int>> data, vector<vector<int>> &res, map<int, int> &map, bool last)
{
    // cout << "\nmulti_fcfs\n";

    vector<vector<int>> nextLevel;

    // for (int i = 0; i < data.size(); ++i)
    // {
    //     if (data[i][1] >= start)
    //         break;

    //     data[i][1] = start;
    // }
    int start = 0, end = 0;
    for (int i = 0; i < data.size(); ++i)
    {
        // cout << "last: " << last << " i: " << i << "\n";
        // cout << "data:\n";
        // for (auto j : data)
        // {
        //     for (auto k : j)
        //         cout << k << " ";
        //     cout << "\n";
        // }
        // cout << "\n";
        // cout << "res:\n";
        // for (auto j : res)
        // {
        //     for (auto k : j)
        //         cout << k << " ";
        //     cout << "\n";
        // }
        // cout << "\n";

        // cout << "map:\n";
        // for (auto i : map)
        // {
        //     cout << i.first << " " << i.second << "\n";
        // }
        // cout << "\n";

        auto it = map.begin();

        for (it = map.begin(); it != map.end(); ++it)
        {
            if (/*it->first <= data[i][1] && */ data[i][1] < it->second)
            {
                start = it->first;
                end = it->second;
                break;
            }
        }
        int num = data[i][0],
            arr = data[i][1],
            burst = data[i][2];

        int cur = start;
        bool idle = 0;
        if (arr > start)
        {
            cur = arr;
            idle = 1;
        }

        if (cur + burst <= end)
        {
            cur += burst;
            data[i][2] = 0;
            res[num][0] += cur;
        }
        else
        {
            data[i][2] = burst - (end - cur);
            if (!last)
                nextLevel.push_back(data[i]);
            else
            {
                // data.push_back(data[i]);
                for (int k = i + 1; k < data.size(); ++k)
                {
                    if (data[k][1] >= end)
                        break;
                    vector<int> tmp = data[k];
                    data[k] = data[k - 1];
                    data[k - 1] = tmp;
                }
                // data.erase(data.begin() + i);
                i--;
            }
            cur = end;
        }

        map.erase(it);

        if (cur < end)
        {
            map.insert({cur, end});
            if (idle)
            {
                map.insert({start, arr});
            }
        }

        // if (last && data[i][2] != 0)
        //     i--;
    }

    return nextLevel;
}

vector<vector<int>> multi_srtf(const vector<vector<int>> data, vector<vector<int>> &res, map<int, int> &map, bool last)
{
    vector<vector<int>> q = {data[0]};
    int ind = 1, start, end;

    auto it = map.begin();

    for (; it != map.end(); ++it)
    {
        if (it->second > q[0][1])
        {
            start = it->first;
            end = it->second;
            break;
        }
    }

    while (ind < data.size() && data[ind][1] < end)
    {
        q.push_back(data[ind]);
        ind++;
    }

    for (int i = 0; i < q.size(); ++i)
    {
        if (q[i][1] < start)
            q[i][1] = start;
    }

    vector<int> pre;
    vector<vector<int>> nextLevel;

    bool touchend = 0, done = 0;

    while (!q.empty() || ind < data.size())
    {
        if (pre.empty())
        {
            if (q.empty())
            {
                q.push_back(data[ind]);
                ind++;
            }

            for (it = map.begin(); it != map.end(); ++it)
            {
                if (it->second > q[0][1])
                {
                    start = it->first;
                    end = it->second;
                    break;
                }
            }

            // int cnt = 0;
            while (ind < data.size() && data[ind][1] < end)
            {
                /*           if (cnt == 0) {
                               q.push_back({ -1,-1,-1 });
                           }*/
                q.push_back(data[ind]);
                ind++;
                // cnt++;
            }

            for (int i = 0; i < q.size(); ++i)
            {
                if (q[i][1] < start)
                    q[i][1] = start;
            }
        }

        sort(q.begin(), q.end(), srtfcmp);

        if (!pre.empty())
        {
            int t = pre[1];
            if (pre[1] < start)
                t = start;

            if (touchend)
            {
                pre[1] = t;
                // if(cnt==0)
                q.push_back(pre);
                // else
                // for (int k = 0; k < q.size(); ++k) {
                //     if (q[k][0] == -1) {
                //         q[k] = pre;
                //         break;
                //     }
                // }
            }
            else
            {
                if (q[0][2] < pre[2])
                    if (last)
                    {
                        pre[1] = t;
                        // if (cnt == 0)
                        q.push_back(pre);
                        // else
                        //     for (int k = 0; k < q.size(); ++k) {
                        //         if (q[k][0] == -1) {
                        //             q[k] = pre;
                        //             break;
                        //         }
                        //     }
                    }
                    else
                    {
                        for (auto k : data)
                        {
                            if (k[0] == pre[0])
                            {
                                pre[1] = k[1];
                                break;
                            }
                        }
                        nextLevel.push_back(pre);
                    }
                else
                {
                    pre[1] = t;
                    q.insert(q.begin(), pre);
                }
            }

            pre.clear();
            continue;
        }

//         cout << "q:\n";
//         for (auto j : q)
//         {
//             for (auto k : j)
//                 cout << k << " ";
//             cout << "\n";
//         }
//         cout << "\n";
//         cout << "map:\n";
//         for (auto i : map)
//         {
//             cout << i.first << " " << i.second << "\n";
//         }
//         cout << "\n";   
//              if(q[0][0]==16)
// exit(0);

        int curNum = q[0][0],
            curArr = q[0][1],
            curBurst = q[0][2];

        touchend = 0;
        done = 0;

        // pre.clear();

        int maxB = curBurst + curArr,
            index = q.size();

        for (int i = 0; i < q.size(); ++i)
        {
            if (q[i][1] != curArr)
            {
                index = i;
                if (maxB > q[i][1])
                {
                    maxB = q[i][1];
                }
                break;
            }
        }

        if (maxB > end)
        {
            touchend = 1;
            maxB = end;
        }

        int diff = maxB - curArr;
        // if (maxB >= curBurst + curArr)
        //     diff = curBurst;
        // else
        //     diff = maxB - curArr;

        for (int i = 0; i < index; ++i)
        {
            q[i][1] += diff;
        }

        q[0][2] -= diff;
        done = 1;

        map.erase(it);
        if (q[0][1] < end)
        {
            map.insert({q[0][1], end});
            if (curArr > start)
            {
                map.insert({start, curArr});
            }
        }

        if (q[0][2] == 0)
        {
            int num = q[0][0];

            // if (num == 16)
            //     exit(0);

            res[num][0] += q[0][1];
            q.erase(q.begin());
        }
        else
        {
            pre = q[0];

            q.erase(q.begin());
            if (touchend)
                if (!last)
                {
                    cc++;
                    // cout << "hello\n";
                    // vector<int> tmp;
                    for (auto j : data)
                    {
                        if (j[0] == pre[0])
                        {
                            // tmp = j;
                            nextLevel.push_back({j[0], j[1], pre[2]});
                            break;
                        }
                    }
                    // nextLevel.push_back({ tmp[0], tmp[1], q[0][2] });

                    // q.erase(q.begin());
                    pre.clear();
                }
            // q.erase(q.begin());

            // else
            //{
            //     // pre = q[0];
            //     q.erase(q.begin());
            // }
        }
    }

    return nextLevel;
}

vector<vector<int>> multi_rr(vector<vector<int>> data, vector<vector<int>> &res, map<int, int> &map, bool last, int timeQ)
{
    // cout << "\nmulti_RR, timeq is " << timeQ << "\n";

    vector<vector<int>> nextLevel;
    vector<vector<int>> queue = {data[0]};

    int cur = data[0][1], start, end;
    for (auto it = map.begin(); it != map.end(); ++it)
    {
        if (it->second > data[0][1])
        {
            start = it->first;
            end = it->second;
            break;
        }
    }

    int ind = 1;
    while (ind < data.size() && data[ind][1] < end)
    {
        queue.push_back(data[ind]);
        ind++;

        // cur = queue[0][1];
    }

    while (!queue.empty() || ind < data.size())
    {
        if (queue.empty())
        {
            queue.push_back(data[ind]);
            ind++;
        }

        if (queue[0][1] > cur)
            cur = queue[0][1];

        bool idle = 0;
        auto it = map.begin();
        for (; it != map.end(); ++it)
        {
            if (it->second > cur)
            {
                start = it->first;
                end = it->second;

                if (cur < start)
                    cur = start;
                if (cur > start)
                    idle = 1;

                break;
            }
        }

        while (ind < data.size() && data[ind][1] < end)
        {
            queue.push_back(data[ind]);
            ind++;

            // cur = queue[0][1];
        }




        vector<int> tmp = queue[0];
        int diff = tmp[2];
        if (diff > timeQ)
            diff = timeQ;
        if (diff > end - cur)
            diff = end - cur;

        queue[0][2] -= diff;
        cur += diff;

        if (queue[0][2] != 0)
        {
            if (last)
                queue.push_back(queue[0]);
            else
                nextLevel.push_back(queue[0]);

            queue.erase(queue.begin());
        }
        else
        {
            int num = queue[0][0];
            res[num][0] += cur;

            queue.erase(queue.begin());
        }

        map.erase(it);
        if (cur < end)
        {
            map.insert({cur, end});
            if (idle)
            {
                map.insert({start, tmp[1]});
            }
        }

        // cout << "last: " << last << "\n";
        // cout << "queue:\n";
        // for (auto j : queue)
        // {
        //     for (auto k : j)
        //         cout << k << " ";
        //     cout << "\n";
        // }
        // cout << "\n";
        // cout << "res:\n";
        // for (auto j : res)
        // {
        //     for (auto k : j)
        //         cout << k << " ";
        //     cout << "\n";
        // }
        // cout << "\n";

        // cout << "map:\n";
        // for (auto i : map)
        // {
        //     cout << i.first << " " << i.second << "\n";
        // }
        // cout << "\n";
        

    }

    return nextLevel;
}
