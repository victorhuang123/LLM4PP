#pragma once

#include<vector>
#include<queue>

using namespace std;

vector<vector<int>> generateInput(int n, int m, int q) {
    vector<vector<int>> edges(m, vector<int>(2));
    vector<vector<int>> queries(q, vector<int>(2));

    for (int i = 0; i < m; i++) {
        edges[i][0] = rand() % n;
        edges[i][1] = rand() % n;
    }

    for (int i = 0; i < q; i++) {
        queries[i][0] = rand() % n;
        queries[i][1] = rand() % n;
    }

    return {edges, queries};
}

vector<bool> baseline(int n, int m, int q, const vector<vector<int>>& edges, const vector<vector<int>>& queries) {
    vector<int> table(n, -1);
    vector<bool> results(q);

    auto parent = [&](int child) {
        queue<int> q;
        while (table[child] != -1) {
            q.push(child);
            child = table[child];
        }
        while (!q.empty()) {
            table[q.front()] = child;
            q.pop();
        }
        return child;
    };

    for (int i = 0; i < m; i++) {
        int s = edges[i][0];
        int t = edges[i][1];

        int ps = parent(s);
        int pt = parent(t);
        if (ps != pt) {
            table[ps] = pt;
        }
    }

    for (int i = 0; i < q; i++) {
        int s = queries[i][0];
        int t = queries[i][1];

        int ps = parent(s);
        int pt = parent(t);

        results[i] = (ps == pt);
    }

    return results;
}