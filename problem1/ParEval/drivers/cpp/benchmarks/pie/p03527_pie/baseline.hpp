#pragma once

#include<vector>
#include<cstring>
#include<functional>
using namespace std;

const int N=400002;

void Link(int x, int y, vector<int> e[N]) {
    e[x].push_back(y);
    e[y].push_back(x);
}

int baseline(char* s, int m, vector<pair<int, int>> edges) {
    int n = strlen(s);
    int c[N], vis[N], sum = 0, tmp = 1;
    vector<int> e[N];

    for(int i = 0; i <= n; i++)
        c[i] = s[i+1] - s[i];

    for(int i = 0; i < n - i; i++)
        Link(i, n - i, e);

    for(auto edge : edges)
        Link(edge.first - 1, edge.second, e);

    function<void(int)> dfs = [&](int i) {
        vis[i] = 1;
        sum += c[i];
        for(int j = 0; j < e[i].size(); j++)
            if(!vis[e[i][j]])
                dfs(e[i][j]);
    };

    dfs(0);
    sum = 0;
    for(int i = 1; i < n; i++)
        if(!vis[i]) {
            dfs(i);
            if(sum % 26)
                tmp = 0;
        }

    return tmp;
}

vector<pair<int, int>> generateInput() {
    vector<pair<int, int>> edges;
    for(int i = 0; i < N; i++) {
        edges.push_back({i, i+1});
    }
    return edges;
}