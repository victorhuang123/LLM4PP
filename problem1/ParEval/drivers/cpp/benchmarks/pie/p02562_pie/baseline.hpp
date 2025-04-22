#pragma once

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
using ll = long long;
using vvl = vector<vector<ll>>;

pair<ll, ll> baseline(vvl& d, ll n, ll t, ll k) {
    struct mcf_graph {
        int n, s, t;
        vector<vector<int>> adj;
        vector<vector<ll>> cap, cost;
        vector<ll> dist;
        vector<int> parent;

        mcf_graph(int n, int s, int t, ll max_cost) : n(n), s(s), t(t), adj(n), cap(n, vector<ll>(n)), cost(n, vector<ll>(n)), dist(n), parent(n) {}

        void add_edge(int u, int v, ll capacity, ll edge_cost) {
            adj[u].push_back(v);
            adj[v].push_back(u);
            cap[u][v] = capacity;
            cost[u][v] = edge_cost;
            cost[v][u] = -edge_cost;
        }

        pair<ll, ll> flow() {
            ll total_flow = 0, total_cost = 0;
            while (true) {
                fill(dist.begin(), dist.end(), LLONG_MAX);
                dist[s] = 0;
                bool updated;
                do {
                    updated = false;
                    for (int u = 0; u < n; ++u) {
                        if (dist[u] == LLONG_MAX) continue;
                        for (int v : adj[u]) {
                            if (cap[u][v] > 0 && dist[v] > dist[u] + cost[u][v]) {
                                dist[v] = dist[u] + cost[u][v];
                                parent[v] = u;
                                updated = true;
                            }
                        }
                    }
                } while (updated);

                if (dist[t] == LLONG_MAX) break;

                ll flow = LLONG_MAX;
                for (int v = t; v != s; v = parent[v]) {
                    int u = parent[v];
                    flow = min(flow, cap[u][v]);
                }

                for (int v = t; v != s; v = parent[v]) {
                    int u = parent[v];
                    cap[u][v] -= flow;
                    cap[v][u] += flow;
                }

                total_flow += flow;
                total_cost += flow * dist[t];
            }
            return {total_flow, total_cost};
        }
    };

    mcf_graph g(102, 100, 101, t);
    for (int i = 0; i < n; i++) {
        g.add_edge(100, i, k, 0);
        g.add_edge(i + 50, 101, k, 0);
        for (int j = 0; j < n; j++) g.add_edge(i, j + 50, 1, -d[i][j]);
    }
    return g.flow();
}

vvl generate_input(ll n) {
    vvl d(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = rand() % 1000000;
        }
    }
    return d;
}