#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

int baseline(int C, int D, int W, int X, vector<vector<int>>& E, vector<vector<int>>& F) {
    vector<vector<vector<vector<int>>>> dp(31, vector<vector<vector<int>>>(51, vector<vector<int>>(15, vector<int>(6, -1)));

    function<int(int, int, int, int)> dfs = [&](int day, int cost, int place, int two) {
        if(dp[day][cost][place][two] >= 0) return dp[day][cost][place][two];
        if(day == D) return 0;

        int ret = 0;

        for(int i = 0; i < C; ++i) ret = max(ret, dfs(day + 1, cost, i, two));

        if(E[place][day] > 0) {
            if(cost + F[place][day] <= W) {
                for(int i = 0; i < C; ++i) ret = max(ret, dfs(day + 1, cost + F[place][day], i, two) + E[place][day]);
            }

            if(two < X) {
                int tcost = cost + F[place][day];
                int tE = E[place][day];
                int now = place - 1;
                while(now >= 0) {
                    if(E[now][day] == 0) break;
                    if(tcost + F[now][day] > W) break;

                    tcost += F[now][day];
                    tE += E[now][day];
                    for(int i = 0; i < C; ++i) ret = max(ret, dfs(day + 1, tcost, i, two + 1) + tE);

                    --now;
                }

                tcost = cost + F[place][day];
                tE = E[place][day];
                now = place + 1;
                while(now < C) {
                    if(E[now][day] == 0) break;
                    if(tcost + F[now][day] > W) break;

                    tcost += F[now][day];
                    tE += E[now][day];
                    for(int i = 0; i < C; ++i) ret = max(ret, dfs(day + 1, tcost, i, two + 1) + tE);
                    ++now;
                }
            }
        }

        dp[day][cost][place][two] = ret;
        return ret;
    };

    int ans = 0;
    for(int i = 0; i < C; ++i) ans = max(ans, dfs(0, 0, i, 0));
    return ans;
}

vector<vector<int>> generateE(int C, int D) {
    vector<vector<int>> E(C, vector<int>(D, 1));
    return E;
}

vector<vector<int>> generateF(int C, int D) {
    vector<vector<int>> F(C, vector<int>(D, 1));
    return F;
}