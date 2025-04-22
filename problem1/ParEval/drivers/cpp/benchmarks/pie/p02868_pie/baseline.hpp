#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long LL;
typedef pair<int, int> PII;
typedef vector<int> VI;

#define MP make_pair
#define PB push_back
#define X first
#define Y second

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define RFOR(i, b, a) for(int i = (b) - 1; i >= (a); --i)
#define ALL(a) a.begin(), a.end()
#define SZ(a) (int)((a).size())
#define FILL(a, value) memset(a, value, sizeof(a))

template<typename T> void setmax(T& x, T y) {x = max(x, y);}
template<typename T> void setmin(T& x, T y) {x = min(x, y);}

const LL INF = 1e9 + 47;
const LL LINF = INF * INF;

LL baseline(int n, int m, vector<int>& l, vector<int>& r, vector<int>& c) {
    vector<vector<pair<int, int>>> g(n + 1);
    FOR(i, 0, m) {
        g[l[i]].PB({r[i], c[i]});
    }
    FOR(i, 1, n) g[i + 1].PB({i, 0});

    vector<LL> d(n + 1, LINF);
    d[1] = 0;
    set<pair<LL, int>> S;
    S.insert({0, 1});

    while(SZ(S)) {
        int v = S.begin()->Y;
        S.erase(S.begin());
        for(auto to: g[v]) {
            if (d[to.X] > d[v] + to.Y) {
                S.erase({d[to.X], to.X});
                d[to.X] = d[v] + to.Y;
                S.insert({d[to.X], to.X});
            }
        }
    }

    if (d[n] == LINF) d[n] = -1;
    return d[n];
}

vector<int> generateInput(int n, int m) {
    vector<int> l(m), r(m), c(m);
    FOR(i, 0, m) {
        l[i] = rand() % n + 1;
        r[i] = rand() % n + 1;
        c[i] = rand() % 1000000 + 1;
    }
    return {l, r, c};
}