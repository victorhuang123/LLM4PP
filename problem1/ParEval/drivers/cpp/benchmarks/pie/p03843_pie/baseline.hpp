#pragma once

#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef long long i64;

i64 baseline(int N, vector<pair<int, int>> edges, vector<char> color) {
    vector<vector<int>> Adj(N + 1);
    vector<int> sz(N + 1), Lo(N + 1), mx1st(N + 1), mx2nd(N + 1);
    i64 answer = 0;

    for (const auto &edge : edges) {
        Adj[edge.first].push_back(edge.second);
        Adj[edge.second].push_back(edge.first);
    }

    auto DFS = [&](int cur, int fa = 0, auto &&DFS) -> void {
        sz[cur] = (color[cur] == '1');
        Lo[cur] = (sz[cur] ? 0 : 0x7F7F7F7F);

        for (const int & to : Adj[cur]) {
            if (to == fa)
                continue;
            DFS(to, cur, DFS);

            int tmp = mx1st[to] + 1;
            if (tmp > mx1st[cur])
                mx2nd[cur] = mx1st[cur], mx1st[cur] = tmp;
            else
                mx2nd[cur] = max(mx2nd[cur], tmp);

            if (sz[to])
                sz[cur] += sz[to], Lo[cur] = min(Lo[cur], tmp);
        }
    };

    auto solve = [&](int cur, int fa = 0, auto &&solve) -> void {
        if (fa) {
            int tmp = (mx1st[fa] == mx1st[cur] + 1 ? mx2nd[fa] : mx1st[fa]) + 1;
            if(tmp > mx1st[cur])
                mx2nd[cur] = mx1st[cur], mx1st[cur] = tmp;
            else
                mx2nd[cur] = max(mx2nd[cur], tmp);
            if(sz[1] - sz[cur])
                Lo[cur] = min(Lo[cur], tmp);
        }

        int delta = min(mx2nd[cur] + 1, mx1st[cur] - 1) - Lo[cur] + 1;
        if(delta > 0)
            answer += delta;

        for(const int & to : Adj[cur])
            if(to != fa)
                solve(to, cur, solve);
    };

    DFS(1, 0, DFS);
    solve(1, 0, solve);

    return answer + 1;
}

vector<pair<int, int>> generateInput(int N) {
    vector<pair<int, int>> edges;
    for (int i = 2; i <= N; ++i) {
        edges.emplace_back(i, i / 2);
    }
    return edges;
}

vector<char> generateColor(int N) {
    vector<char> color(N + 1, '0');
    for (int i = 1; i <= N; ++i) {
        if (i % 2 == 0) color[i] = '1';
    }
    return color;
}