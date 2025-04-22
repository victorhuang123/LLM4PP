#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long LL;

struct node {
    int from, to, w;
};

int baseline(int k) {
    const int MAXN = 1000005;
    vector<node> G(MAXN);
    vector<int> dist(MAXN, 0x3f3f3f3f);
    vector<int> head(MAXN, -1);
    vector<bool> vis(MAXN, false);
    int cnt = 0;

    auto add = [&](int u, int v, int w) {
        G[cnt].to = v;
        G[cnt].w = w;
        G[cnt].from = head[u];
        head[u] = cnt++;
    };

    auto spfa = [&](int s) {
        queue<int> q;
        q.push(s);
        vis[s] = true;
        dist[s] = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int i = head[u]; ~i; i = G[i].from) {
                int v = G[i].to;
                if (dist[v] > dist[u] + G[i].w) {
                    dist[v] = dist[u] + G[i].w;
                    if (!vis[v]) {
                        vis[v] = true;
                        q.push(v);
                    }
                }
            }
        }
    };

    for (int i = 0; i < k; ++i) {
        add(i, (i + 1) % k, 1);
        add(i, i * 10 % k, 0);
    }
    spfa(1);
    return dist[0] + 1;
}

vector<int> generateInput() {
    return {1000000};
}