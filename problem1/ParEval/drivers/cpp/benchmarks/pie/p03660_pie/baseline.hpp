#pragma once

#include <vector>
#include <cstring>

using namespace std;

const int MAXN = 1e5 + 10;

int head[MAXN], net[2 * MAXN], u[2 * MAXN], v[2 * MAXN], tot;
int num1[MAXN], num2[MAXN];

void add(int l, int r) {
    u[++tot] = l; v[tot] = r; net[tot] = head[l]; head[l] = tot;
}

void dfs(int now, int step, int flag, int vt[], int num1[], int num2[]) {
    vt[now] = 1;
    if (flag == 1) num1[now] = step;
    if (flag == 2) num2[now] = step;
    for (int i = head[now]; i; i = net[i])
        if (vt[v[i]] == 0)
            dfs(v[i], step + 1, flag, vt, num1, num2);
}

int baseline(int n, const vector<vector<int>>& edges) {
    tot = 0;
    memset(head, 0, sizeof(head));
    memset(net, 0, sizeof(net));
    memset(u, 0, sizeof(u));
    memset(v, 0, sizeof(v));
    memset(num1, 0, sizeof(num1));
    memset(num2, 0, sizeof(num2));

    for (const auto& edge : edges) {
        int l = edge[0], r = edge[1];
        add(l, r);
        add(r, l);
    }

    int vt[MAXN];
    memset(vt, 0, sizeof(vt));
    dfs(1, 0, 1, vt, num1, num2);

    memset(vt, 0, sizeof(vt));
    dfs(n, 0, 2, vt, num1, num2);

    int p1 = 0, p2 = 0;
    for (int i = 1; i <= n; i++) {
        if (num1[i] < num2[i])
            p1++;
        if (num2[i] < num1[i])
            p2++;
        if (num1[i] == num2[i])
            p1++;
    }

    return p1 > p2 ? 1 : 2;
}

vector<vector<int>> generateInput(int n) {
    vector<vector<int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.push_back({i, i + 1});
    }
    return edges;
}