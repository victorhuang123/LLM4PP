#pragma once

#include <vector>
#include <queue>

using namespace std;

bool baseline(int N, int E, vector<vector<int>>& in, vector<vector<int>>& out) {
    queue<int> S, L;
    bool multi_flag = false;

    for (int i = 1; i <= N; i++) {
        bool has_incoming = false;
        for (int j = 0; j < in[i].size(); j++) {
            if (in[i][j] != -1) {
                has_incoming = true;
                break;
            }
        }
        if (!has_incoming) S.push(i);
    }

    while (!S.empty()) {
        int u = S.front(); S.pop();
        L.push(u);
        int entered = 0;
        for (int i = 0; i < out[u].size(); i++) {
            int to = out[u][i];
            for (int j = 0; j < in[to].size(); j++) {
                if (in[to][j] == u) in[to][j] = -1;
            }

            bool has_incoming = false;
            for (int j = 0; j < in[to].size(); j++) {
                if (in[to][j] != -1) {
                    has_incoming = true;
                    break;
                }
            }
            if (!has_incoming) {
                S.push(to);
                entered++;
            }
        }
        if (entered >= 2) multi_flag = true;
    }

    return multi_flag;
}

vector<vector<int>> generate_input(int N, int E) {
    vector<vector<int>> in(N + 1), out(N + 1);
    for (int i = 0; i < E; i++) {
        int u = rand() % N + 1;
        int v = rand() % N + 1;
        out[u].push_back(v);
        in[v].push_back(u);
    }
    return {in, out};
}