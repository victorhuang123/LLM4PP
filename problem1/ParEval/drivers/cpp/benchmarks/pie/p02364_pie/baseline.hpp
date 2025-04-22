#pragma once

#include <queue>
#include <vector>
#include <climits>

using namespace std;

#define MAX_E 10001
#define MAX_V 100001
#define INF INT_MAX

typedef struct edge {
    int from;
    int to;
    int cost;
} edge;

struct cost_cmp {
    bool operator()(edge x, edge y) const {
        return (x.cost) > (y.cost);
    }
};

int baseline(int start, int V, int E, vector<edge>& edges) {
    vector<vector<edge>> G(V);
    vector<bool> used(V, false);
    int res = 0;

    for (const auto& e : edges) {
        G[e.from].push_back(e);
    }

    priority_queue<edge, vector<edge>, cost_cmp> que;
    que.push({start, start, 0});

    while (!que.empty()) {
        edge p = que.top(); que.pop();
        int v = p.to;

        if (used[v]) continue;

        used[v] = true;
        res += p.cost;

        for (const auto& e : G[v]) {
            int to = e.to;
            if (!used[to]) que.push(e);
        }
    }

    return res;
}

vector<edge> generateInput(int V, int E) {
    vector<edge> edges(E);
    for (int i = 0; i < E; ++i) {
        edges[i] = {rand() % V, rand() % V, rand() % 1000};
    }
    return edges;
}