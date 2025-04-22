#pragma once

#include <queue>
#include <vector>
#include <algorithm>

#define INF 1e18
#define int long long
typedef pair<int,int> P;
#define MP make_pair

int baseline(int n, int m, int k, int s, int p, int q, const vector<int>& zonbi, const vector<P>& edges) {
    vector<int> dis(n + 1, INF);
    vector<int> costco(n + 1, INF);
    priority_queue<P, vector<P>, greater<P>> pq;
    vector<vector<int>> pairs(n + 1);

    for (int i = 0; i < m; i++) {
        int x = edges[i].first;
        int y = edges[i].second;
        pairs[x].push_back(y);
        pairs[y].push_back(x);
    }

    for (int i = 0; i < k; i++) {
        pq.push(MP(0, zonbi[i]));
        dis[zonbi[i]] = 0;
    }

    while (!pq.empty()) {
        int cost = pq.top().first;
        int start = pq.top().second;
        pq.pop();
        if (s == cost) continue;
        for (int j = 0; j < pairs[start].size(); j++) {
            if (dis[pairs[start][j]] > cost + 1) {
                dis[pairs[start][j]] = cost + 1;
                pq.push(MP(cost + 1, pairs[start][j]));
            }
        }
    }

    pq.push(MP(0, 1));
    costco[1] = 0;

    while (!pq.empty()) {
        int cost = pq.top().first;
        int start = pq.top().second;
        pq.pop();
        for (int i = 0; i < pairs[start].size(); i++) {
            int hoge;
            if (dis[pairs[start][i]] == 0) {
                continue;
            } else if (dis[pairs[start][i]] == INF) {
                hoge = p;
            } else {
                hoge = q;
            }
            if (pairs[start][i] == n) {
                hoge = 0;
            }
            if (costco[pairs[start][i]] > cost + hoge) {
                costco[pairs[start][i]] = cost + hoge;
                pq.push(MP(cost + hoge, pairs[start][i]));
            }
        }
    }

    return costco[n];
}

vector<int> generateInput(int n, int m, int k, int s, int p, int q) {
    vector<int> zonbi(k);
    vector<P> edges(m);

    for (int i = 0; i < k; i++) {
        zonbi[i] = rand() % n + 1;
    }

    for (int i = 0; i < m; i++) {
        int x = rand() % n + 1;
        int y = rand() % n + 1;
        edges[i] = MP(x, y);
    }

    return {n, m, k, s, p, q, zonbi, edges};
}