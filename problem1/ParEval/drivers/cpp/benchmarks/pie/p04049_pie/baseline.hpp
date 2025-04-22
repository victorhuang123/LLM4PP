#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

const int maxn=1e5+5;

vector<int> ma[maxn];

void dfs(int f, int t, int deep, LL& cnt1) {
    cnt1++;
    if(deep == 0) return;
    for(int i = 0; i < ma[f].size(); i++) {
        if(ma[f][i] != t) {
            dfs(ma[f][i], f, deep-1, cnt1);
        }
    }
}

int baseline(int n, int k, vector<int>& u, vector<int>& v) {
    for(int i = 0; i <= n; i++) {
        ma[i].clear();
    }

    for(int i = 1; i <= n-1; i++) {
        ma[u[i-1]].push_back(v[i-1]);
        ma[v[i-1]].push_back(u[i-1]);
    }

    LL ans = 0;

    if(k % 2 == 1) {
        for(int i = 1; i <= n-1; i++) {
            LL cnt = 0, cnt1 = 0;
            dfs(u[i-1], v[i-1], k/2, cnt1);
            cnt += cnt1;
            cnt1 = 0;
            dfs(v[i-1], u[i-1], k/2, cnt1);
            cnt += cnt1;
            ans = max(ans, cnt);
        }
    } else {
        for(int i = 1; i <= n; i++) {
            LL cnt = 0, cnt1 = 0;
            dfs(i, 0, k/2, cnt1);
            cnt += cnt1;
            ans = max(ans, cnt);
        }
    }

    return n - ans;
}

vector<int> generateInput(int n) {
    vector<int> u(n-1), v(n-1);
    for(int i = 0; i < n-1; i++) {
        u[i] = i+1;
        v[i] = i+2;
    }
    return u, v;
}