#pragma once

#include<vector>
#include<queue>
#include<utility>
#include<algorithm>

using namespace std;

typedef struct E {
    int to, cost;
} edge;

const int MAX_V = 200100;
const int Inf = 1e9;

vector<int> baseline(int a, int b, int r, vector<vector<edge>>& E) {
    vector<int> d(MAX_V, Inf);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> que;

    d[r] = 0;
    que.push(make_pair(0, r));

    while (!que.empty()) {
        pair<int, int> p = que.top(); que.pop();
        int v = p.second;

        if (d[v] < p.first) continue;

        for (int j = 0; j < E[v].size(); j++) {
            edge t = E[v][j];
            if (d[t.to] > d[v] + t.cost) {
                d[t.to] = d[v] + t.cost;
                que.push(make_pair(d[t.to], t.to));
            }
        }
    }

    vector<int> result;
    for (int i = 0; i < a; i++) {
        if (d[i] == Inf) result.push_back(-1); // Use -1 to represent INF
        else result.push_back(d[i]);
    }

    return result;
}

vector<vector<edge>> generateInput() {
    int a = 200000; // Maximum number of vertices
    int b = 400000; // Maximum number of edges
    int r = 0; // Starting vertex

    vector<vector<edge>> E(a);
    for (int i = 0; i < b; i++) {
        int u = rand() % a;
        int v = rand() % a;
        int cost = rand() % 1000;
        E[u].push_back({v, cost});
    }

    return E;
}