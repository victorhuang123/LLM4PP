#pragma once

#include <bits/stdc++.h>

using namespace std;

#define pii pair<int, int>
#define pll pair<long long, long long>
#define fi first
#define se second
#define mp make_pair
#define pb push_back

#define INF 0x3f3f3f3f3f3f3f3f
#define MAXN 200005
#define MOD 1000000007LL

int p[MAXN], col[MAXN];
vector<int> v[MAXN];

void join(int x, int y, int st) {
    x = p[x], y = p[y];
    if (x == y) return;
    if (v[x].size() < v[y].size())
        swap(x, y);

    int col_shift = col[x]+st+3-col[y];

    int src = p[y];
    for (int i = 0; i < v[src].size(); i++) {
        int q = v[src][i];
        p[q] = p[x];
        v[p[x]].pb(q);
        (col[q] += col_shift) %= 3;
    }
    v[src].clear();
}

int baseline(int n, int m, vector<pair<pii, int>>& games, int go) {
    for (int i = 0; i < n; i++) {
        p[i] = i;
        v[i].clear();
        v[i].pb(i);
        col[i] = 0;
    }

    for (int i = 0; i < m; i++) {
        int u, v, st;
        u = games[i].fi.fi;
        v = games[i].fi.se;
        st = games[i].se;

        if (u == go || v == go)
            continue;

        if (p[u] != p[v]) {
            join(u, v, st);
        }
        else {
            if ((col[u]+st)%3 != col[v])
                return i;
        }
    }

    return -1;
}

vector<pair<pii, int>> generateInput(int n, int m) {
    vector<pair<pii, int>> games(m);
    for (int i = 0; i < m; i++) {
        int u = rand() % n;
        int v = rand() % n;
        int st = rand() % 3;
        games[i] = mp(mp(u, v), st);
    }
    return games;
}