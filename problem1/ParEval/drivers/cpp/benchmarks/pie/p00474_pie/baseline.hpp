#pragma once

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define PB push_back
#define INF (1LL<<61LL)

typedef pair<int, int> pii;

int baseline(int N, int L, vector<int>& a) {
    vector<int> g[N+1];
    bool flg[N+1] = {false};
    int dx[] = {-1, 1};

    for (int i = 1; i <= N; ++i) {
        int count = 0;
        for (int j = 0; j < 2; ++j) {
            if (a[i + dx[j]] < a[i]) {
                g[i].PB(i + dx[j]);
                count++;
            }
        }

        if ((count == 2) || (((i == 1) || (i == N)) && (count == 1)))
            flg[i] = true;
    }

    function<int(int)> cal = [&](int x) {
        int res = L - a[x], temp = 0;
        for (int i = 0; i < g[x].size(); ++i) {
            temp = max(temp, cal(g[x][i]));
        }
        return res + temp;
    };

    int maxt = 0;
    for (int i = 1; i <= N; ++i) {
        if (!flg[i]) continue;
        maxt = max(maxt, cal(i));
    }

    return maxt;
}

vector<int> generateInput(int N) {
    vector<int> a(N + 2);
    for (int i = 1; i <= N; ++i) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}