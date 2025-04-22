#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll inf = 0x3f3f3f3f3f3f3f3f;

vector<ll> baseline(int v, int e, int r, vector<tuple<int, int, ll>>& edges) {
    vector<ll> dist(v, inf);
    vector<vector<pair<ll, int>>> adj(v);
    bitset<100005> inq;
    vector<int> q(100005);
    int qh = 0, qt = 0, ct = 0;

    auto qpop = [&]() {
        int v = q[qh++];
        if (qh > 100005) qh = 0;
        return v;
    };

    auto qpush = [&](int v) {
        ct++;
        q[qt++] = v;
        if (qt > 100005) qt = 0;
    };

    for (int i = 0; i < e; i++) {
        int s = get<0>(edges[i]);
        int t = get<1>(edges[i]);
        ll d = get<2>(edges[i]);
        adj[s].push_back({ d, t });
    }

    dist[r] = 0;
    qpush(r);

    while (qh != qt) {
        if (ct > 2 * v * e + 5) {
            return vector<ll>();
        }
        int p = qpop();
        inq[p] = false;
        for (auto h : adj[p]) {
            int t = h.second;
            ll d = h.first + dist[p];
            if (d < dist[t]) {
                dist[t] = d;
                if (!inq[t])
                    inq[t] = true, qpush(t);
            }
        }
    }

    return dist;
}

vector<tuple<int, int, ll>> generateInput(int v, int e) {
    vector<tuple<int, int, ll>> edges(e);
    for (int i = 0; i < e; i++) {
        int s = rand() % v;
        int t = rand() % v;
        ll d = rand() % 1000000;
        edges[i] = {s, t, d};
    }
    return edges;
}