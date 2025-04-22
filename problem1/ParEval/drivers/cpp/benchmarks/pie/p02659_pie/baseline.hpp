#pragma once

#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
#include <climits>

using namespace std;

struct edge {
    int to;
    double cost;
};

using P = pair<double, int>;

double baseline(int V, const vector<vector<edge>>& G, int s) {
    const double INF = 1e9;
    vector<double> d(V, INF);
    priority_queue<P, vector<P>, greater<P>> que;
    d[s] = 0;
    que.push(P(0, s));

    while (!que.empty()) {
        P p = que.top();
        que.pop();
        int v = p.second;
        if (d[v] < p.first) continue;
        for (const edge& e : G[v]) {
            if (d[e.to] > d[v] + e.cost) {
                d[e.to] = d[v] + e.cost;
                que.push(P(d[e.to], e.to));
            }
        }
    }

    return *max_element(d.begin(), d.end());
}

vector<vector<edge>> generateInput(int V) {
    vector<vector<edge>> G(V);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j) {
                G[i].push_back({j, static_cast<double>(rand() % 100 + 1)});
            }
        }
    }
    return G;
}