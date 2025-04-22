#pragma once

#include <bits/stdc++.h>

using namespace std;

const int N = 16;

long long baseline(int n, const vector<int>& x, const vector<int>& y) {
    int chk[N];
    vector<int> a[N];
    map<pair<int, int>, int> M;
    long long ans = 0;

    function<void(int)> dfs = [&](int step) {
        if (step == n / 2) {
            long long rlt = 0;
            for (int i = 0; i < N / 2; i++) a[i].clear();
            for (int i = 0; i < n; i++) a[chk[i]].push_back(i);
            M.clear();
            for (int i = 0; i < n / 2 + 1; i++) if (a[i].size() == 2) {
                int dx = abs(x[a[i][0]] - x[a[i][1]]);
                int dy = (y[a[i][0]] - y[a[i][1]]) * ((x[a[i][0]] - x[a[i][1]] < 0) ? -1 : 1);
                int gcd = __gcd(dx, dy);
                dx /= gcd, dy /= gcd;
                M[make_pair(dx, dy)]++;
            }
            for (map<pair<int, int>, int> :: iterator it = M.begin(); it != M.end(); it++) rlt += 1LL * it->second * (it->second - 1) / 2;
            ans = max(ans, rlt);
            return;
        }
        for (int i = 0; i < n; i++) {
            if (chk[i] != -1) continue;
            chk[i] = step;
            for (int j = i + 1; j < n; j++) {
                if (chk[j] != -1) continue;
                chk[j] = step;
                dfs(step + 1);
                chk[j] = -1;
            }
            chk[i] = -1;
            break;
        }
    };

    memset(chk, -1, sizeof chk);
    dfs(0);
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) {
        x[i] = rand() % 1000;
        y[i] = rand() % 1000;
    }
    return {x, y};
}