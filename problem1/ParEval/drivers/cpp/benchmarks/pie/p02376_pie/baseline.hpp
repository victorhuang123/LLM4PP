#pragma once

#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

const int MaxV = 100000;
const int iINF = 1e9;

struct edge {
    int to, cap, rev;
};

vector<edge> graph[MaxV];
bool used[MaxV];

void addEdge(int from, int to, int cap) {
    graph[from].push_back({to, cap, (int)graph[to].size()});
    graph[to].push_back({from, 0, (int)graph[from].size() - 1});
}

int dfs(int v, int t, int f) {
    if (v == t) return f;
    used[v] = true;

    for (auto &e : graph[v]) {
        if (!used[e.to] && e.cap > 0) {
            int d = dfs(e.to, t, min(f, e.cap));

            if (d > 0) {
                e.cap -= d;
                graph[e.to][e.rev].cap += d;
                return d;
            }
        }
    }

    return 0;
}

int maxFlow(int s, int t) {
    int flow = 0;
    for (;;) {
        memset(used, false, sizeof(used));

        int f = dfs(s, t, iINF);

        if (f == 0) return flow;

        flow += f;
    }
}

int baseline(int V, int E, vector<tuple<int, int, int>>& edges) {
    for (int i = 0; i < E; i++) {
        int s, t, c;
        tie(s, t, c) = edges[i];
        addEdge(s, t, c);
    }

    return maxFlow(0, V - 1);
}

vector<tuple<int, int, int>> generateInput(int V, int E) {
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < E; i++) {
        int s = rand() % V;
        int t = rand() % V;
        int c = rand() % 1000 + 1;
        edges.emplace_back(s, t, c);
    }
    return edges;
}