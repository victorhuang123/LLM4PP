#pragma once

#include<vector>
#include<algorithm>

struct Edge {
    int n1, n2, cost;
};

int find1(int x, std::vector<int>& fa) {
    if(x == fa[x])
        return x;
    fa[x] = find1(fa[x], fa);
    return fa[x];
}

int baseline(int n, int m, const std::vector<Edge>& edges) {
    std::vector<int> fa(n + 1);
    for(int i = 0; i <= n; i++)
        fa[i] = i;

    std::vector<Edge> sortedEdges = edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge& a, const Edge& b) {
        return a.cost < b.cost;
    });

    int num = 0;
    for(const auto& e : sortedEdges) {
        int a = find1(e.n1, fa);
        int b = find1(e.n2, fa);
        if(a == b)
            continue;
        fa[a] = fa[b];
        num++;
        if(num == (n + 1) / 2) {
            return e.cost;
        }
    }
    return -1;
}

std::vector<Edge> generateInput(int n, int m) {
    std::vector<Edge> edges(m);
    for(int i = 0; i < m; i++) {
        edges[i].n1 = rand() % n + 1;
        edges[i].n2 = rand() % n + 1;
        edges[i].cost = rand() % 100000 + 1;
    }
    return edges;
}