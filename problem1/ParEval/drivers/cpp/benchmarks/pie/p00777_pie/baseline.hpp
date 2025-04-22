#pragma once

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef pair<int, int> pii;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)

#define INF (1e9 + 1)

#define MAX_V 800

struct edge { int to, weight; };

pii dfs(int prev, int v, const vector<edge> graph[MAX_V]) {
    pii r(0, v);
    rep(i, graph[v].size()) {
        struct edge e = graph[v][i];
        if (e.to == prev) continue;
        pii tmp = dfs(v, e.to, graph);
        tmp.first += e.weight;
        if (r.first < tmp.first) r = tmp;
    }
    return r;
}

int diameter(const vector<edge> graph[MAX_V], int v) {
    int s = 0;
    while (graph[s].size() == 0 && s < v) s++;
    if (s == v) return 0;
    pii r = dfs(-1, s, graph);
    pii t = dfs(-1, r.second, graph);
    return t.first;
}

int baseline(int v, const vector<int>& tmp, const vector<int>& weights) {
    int sum = 0, lsum = 0;
    vector<edge> G[MAX_V];
    rep(i, v - 1) {
        int c = weights[i];
        G[i + 1].push_back(edge{tmp[i] - 1, c});
        G[tmp[i] - 1].push_back(edge{(int)i + 1, c});
        sum += c;
    }
    bool used[MAX_V][MAX_V] = {};
    rep(i, v) {
        if (G[i].size() == 1) {
            int from = min<int>(i, G[i][0].to);
            int to = max<int>(i, G[i][0].to);
            if (used[from][to]) continue;
            used[from][to] = true;
            lsum += G[i][0].weight;
        }
    }
    vector<bool> isLeaf(v, false);
    rep(i, v) if (G[i].size() == 1) isLeaf[i] = true;
    vector<edge> gr[MAX_V];
    rep(i, v) {
        if (isLeaf[i]) continue;
        for (auto &e : G[i]) {
            if (isLeaf[e.to]) continue;
            gr[i].push_back(e);
        }
    }
    return sum * 3 - lsum * 2 - diameter(gr, v);
}

vector<int> generateInput(int v) {
    vector<int> tmp(v - 1), weights(v - 1);
    for (int i = 0; i < v - 1; ++i) {
        tmp[i] = i + 2;
        weights[i] = 1;
    }
    return tmp, weights;
}