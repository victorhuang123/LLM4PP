#pragma once

#include <vector>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;
typedef long long ll;
#define rep(i,n) for(int i=0;i<(n);++i)
#define INF 2147483600
const int V=200010;
using P=pair<int,int>;

vector<vector<P>> generateInput(ll n, ll m) {
    vector<vector<P>> G(V);
    ll a, b;
    rep(i, m) {
        a = rand() % n + 1;
        b = rand() % n + 1;
        G[a].emplace_back(1, b);
        G[b].emplace_back(1, a);
    }
    return G;
}

bool baseline(ll n, ll m, const vector<vector<P>>& G) {
    vector<int> dist(V, INF);
    vector<bool> used(V, false);
    priority_queue<P, vector<P>, greater<P>> q;
    q.push(P(0, 1));
    while (!q.empty()) {
        int d, t;
        tie(d, t) = q.top(); q.pop();
        if (used[t]) continue;
        used[t] = true;
        dist[t] = d;
        for (P e : G[t]) {
            if (dist[e.second] <= d + e.first) continue;
            q.push(P(d + e.first, e.second));
        }
    }
    return dist[n] <= 2;
}