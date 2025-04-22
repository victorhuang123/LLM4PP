#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        edges[i] = {rand() % n + 1, rand() % n + 1};
    }
    return edges;
}

bool baseline(int n, int m, string s, vector<pair<int, int>> edges) {
    int v, u;
    vector<int> degA(n, 0), degB(n, 0), mark(n, 0);
    vector<vector<int>> adj_matrix(n);
    vector<int> que;

    for (int i = 0; i < m; i++) {
        v = edges[i].first;
        u = edges[i].second;
        v--; u--;

        if (v == u) {
            adj_matrix[v].push_back(v);
            degA[v] += (s[v] == 'A');
            degB[v] += (s[v] == 'B');
        } else {
            adj_matrix[v].push_back(u);
            adj_matrix[u].push_back(v);
            degA[v] += (s[u] == 'A');
            degB[v] += (s[u] == 'B');
            degA[u] += (s[v] == 'A');
            degB[u] += (s[v] == 'B');
        }
    }

    for (int i = 0; i < n; i++) {
        if (degA[i] == 0 || degB[i] == 0) {
            que.push_back(i);
            mark[i] = true;
        }
    }

    int i = 0;
    while (que.size() < n && i < que.size()) {
        int v = que[i];
        for (int j : adj_matrix[v]) {
            if (mark[j]) continue;
            degA[j] -= (s[v] == 'A');
            degB[j] -= (s[v] == 'B');

            if (degA[j] == 0 || degB[j] == 0) {
                que.push_back(j);
                mark[j] = true;
            }
        }
        i++;
    }

    return que.size() < n;
}