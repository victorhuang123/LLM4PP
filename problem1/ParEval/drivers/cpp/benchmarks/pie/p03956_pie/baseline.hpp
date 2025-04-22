#pragma once

#include<vector>
#include<utility>
using namespace std;

typedef long long ll;

ll baseline(int n, int m, vector<pair<int, int>>& edges) {
    int flag, cnt[3], ncnt, ecnt;
    vector<int> c(n + 1);
    vector<bool> vis(n + 1), evis(m + 1);
    struct node {
        int v, w, id;
        node(int _v, int _w, int _id): v(_v), w(_w), id(_id) {}
    };
    vector<vector<node>> E(n + 1);

    for(int i = 1; i <= m; i++) {
        int u = edges[i-1].first, v = edges[i-1].second;
        E[u].emplace_back(v, 1, i);
        E[v].emplace_back(u, -1, i);
    }

    auto dfs = [&](int u, auto&& dfs) -> void {
        vis[u] = 1;
        ncnt++;
        cnt[c[u]]++;
        for(int i = 0; i < (int)E[u].size(); i++) {
            int v = E[u][i].v, w = E[u][i].w, id = E[u][i].id;
            if(evis[id]) continue; evis[id] = 1; ecnt++;
            if(!vis[v]) {
                c[v] = (c[u] + w + 3) % 3;
                dfs(v, dfs);
            } else if(c[v] != (c[u] + w + 3) % 3) flag = 1;
        }
    };

    ll ans = 0;
    for(int i = 1; i <= n; i++) {
        if(vis[i]) continue;
        flag = ncnt = ecnt = cnt[0] = cnt[1] = cnt[2] = 0;
        dfs(i, dfs);
        if(flag) ans += 1ll * ncnt * ncnt;
        else if(!cnt[0] || !cnt[1] || !cnt[2]) ans += ecnt;
        else ans += 1ll * cnt[0] * cnt[1] + 1ll * cnt[1] * cnt[2] + 1ll * cnt[2] * cnt[0];
    }
    return ans;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for(int i = 0; i < m; i++) {
        edges.emplace_back(rand() % n + 1, rand() % n + 1);
    }
    return edges;
}