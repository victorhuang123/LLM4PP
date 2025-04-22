#pragma once

#include <bits/stdc++.h>

#define MOD 1000000007
#define INF 1061109567
#define pb push_back
#define in(s) freopen(s,"r",stdin);
#define out(s) freopen(s,"w",stdout);
#define fi first
#define se second
#define bw(i,r,l) for (int i=r-1;i>=l;i--)
#define fw(i,l,r) for (int i=l;i<r;i++)
#define fa(i,x) for (auto i:x)

using namespace std;

const int N=1e5+5;

int baseline(int n, int L, const vector<int>& x, const vector<pair<int, int>>& queries) {
    vector<vector<int>> sp(N, vector<int>(20, -1));
    fw (i,0,n) sp[i][0] = upper_bound(x.begin(), x.end(), x[i] + L) - x.begin() - 1;
    fw (j,1,18) fw (i,0,n) if (sp[i][j-1] != -1) sp[i][j] = sp[sp[i][j-1]][j-1];
    int total = 0;
    fa (query, queries) {
        int a = query.first, b = query.second;
        if (a > b) swap(a, b);
        int ans = 1;
        bw (i,18,0) if (sp[a-1][i] != -1 && sp[a-1][i] < b-1) a = sp[a-1][i], ans += (1 << i);
        total += ans;
    }
    return total;
}

vector<int> generateInput(int n) {
    vector<int> x(n);
    fw (i,0,n) x[i] = i + 1;
    return x;
}

vector<pair<int, int>> generateQueries(int q, int n) {
    vector<pair<int, int>> queries(q);
    fw (i,0,q) queries[i] = {1, n};
    return queries;
}