#pragma once

#include<vector>
#include<algorithm>
#include<cstring>

using namespace std;

typedef long long LL;

int baseline(int N, vector<pair<int, int>>& edges) {
    vector<vector<int>> G(N + 1);
    vector<vector<int>> cnt(N + 1, vector<int>(21, 0));

    for(auto& edge : edges) {
        int u = edge.first, v = edge.second;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    int ans = 0;
    function<void(int, int)> DFS = [&](int u, int fa) {
        for(int v : G[u]) {
            if(v == fa) continue;
            DFS(v, u);
            for(int j = 0; j < 20; j++)
                cnt[u][j] += cnt[v][j];
        }

        int val = 0;
        for(int i = 20; i >= 0; i--)
            if(cnt[u][i] >= 2) {
                val = i + 1;
                break;
            }

        while(cnt[u][val] == 1)
            val++;

        ans = max(ans, val);
        cnt[u][val]++;
        for(int i = 0; i < val; i++)
            cnt[u][i] = 0;
    };

    DFS(1, -1);
    return ans;
}

vector<pair<int, int>> generateInput(int N) {
    vector<pair<int, int>> edges;
    for(int i = 2; i <= N; i++) {
        edges.push_back({i, i / 2});
    }
    return edges;
}