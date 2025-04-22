#pragma once

#include<vector>
#include<queue>
#include<cstring>

struct Tree {
    struct edge{int next,to;};
    std::vector<int> head;
    std::vector<edge> a;
    int cnt;

    Tree(int n) : head(n + 1), a(2 * (n + 1)), cnt(0) {}

    void link(int x, int y) {
        a[++cnt] = {head[x], y}; head[x] = cnt;
        a[++cnt] = {head[y], x}; head[y] = cnt;
    }
};

int baseline(int n, int p1, int p2, Tree& A, Tree& B) {
    std::vector<int> dep(n + 1, -1), dis(n + 1, -1), fr(n + 1), vis(n + 1);
    std::queue<int> Q;
    int ans = 0;

    auto bfs1 = [&]() {
        std::fill(dis.begin(), dis.end(), -1);
        if(dep[p1]) Q.push(p1); dis[p1] = 0;
        while(!Q.empty()) {
            int x = Q.front(); Q.pop(); vis[x] = 1;
            for(int i = A.head[x]; i; i = A.a[i].next) {
                int R = A.a[i].to;
                if(dis[R] == -1) {
                    dis[R] = dis[x] + 1;
                    if(dis[R] < dep[R]) Q.push(R);
                    else if(dis[R] == dis[R]) vis[R] = 1;
                }
            }
        }
    };

    auto bfs2 = [&]() {
        std::fill(dep.begin(), dep.end(), -1);
        Q.push(p2); dep[p2] = 0;
        while(!Q.empty()) {
            int x = Q.front(); Q.pop();
            for(int i = B.head[x]; i; i = B.a[i].next) {
                int R = B.a[i].to;
                if(dep[R] == -1) dep[R] = dep[x] + 1, fr[R] = x, Q.push(R);
            }
        }
    };

    auto Dis = [&](int x, int y) {
        if(dep[x] < dep[y]) std::swap(x, y);
        if(fr[x] == fr[y] || x == y || fr[x] == y) return 0;
        if(fr[fr[x]] == y) return 0;
        return 1;
    };

    bfs2(); bfs1();
    for(int x = 1; x <= n; x++) {
        for(int i = A.head[x]; i; i = A.a[i].next) {
            if(vis[x] && vis[A.a[i].to] && Dis(x, A.a[i].to)) {
                return -1;
            }
        }
    }
    for(int i = 1; i <= n; i++) if(vis[i]) ans = std::max(dep[i], ans);
    return ans * 2;
}

std::pair<Tree, Tree> generateInput(int n) {
    Tree A(n), B(n);
    for(int i = 1; i < n; i++) {
        A.link(i, i + 1);
        B.link(i, i + 1);
    }
    return {A, B};
}