#pragma once

#include <vector>
#include <functional>

using namespace std;

struct edge { int to, id; };

vector<long long> baseline(int n, vector<int>& a, vector<int>& b, vector<long long>& s) {
    vector<edge> g[200009];
    int vc = 0;
    long long sd = 0;
    vector<long long> ans(n - 1, -1);
    vector<int> c(n, 0);
    vector<long long> dist(n, 0);

    for (int i = 0; i < n - 1; i++) {
        a[i]--, b[i]--;
        g[a[i]].push_back(edge{ b[i], i });
        g[b[i]].push_back(edge{ a[i], i });
    }

    function<void(int, int)> dfs = [&](int pos, int pre) {
        c[pos] = 1;
        for (edge e : g[pos]) {
            if (e.to != pre) {
                dfs(e.to, pos);
                c[pos] += c[e.to];
                if (n - c[e.to] * 2 != 0) {
                    ans[e.id] = (s[e.to] - s[pos]) / (n - c[e.to] * 2);
                }
            }
        }
    };

    function<void(int, int, int)> dfs2 = [&](int pos, int pre, int flag) {
        if (flag) vc++;
        sd += dist[pos];
        for (edge e : g[pos]) {
            if (e.to != pre) {
                dist[e.to] = dist[pos];
                if (ans[e.id] != -1) dist[e.to] += ans[e.id];
                dfs2(e.to, pos, (flag | (ans[e.id] == -1 ? 1 : 0)));
            }
        }
    };

    dfs(0, -1);

    int zp = -1;
    for (int i = 0; i < n - 1; i++) {
        if (ans[i] == -1) zp = i;
    }

    if (zp != -1) {
        dfs2(0, -1, 0);
        ans[zp] = (s[0] - sd) / vc;
    }

    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n - 1), b(n - 1);
    vector<long long> s(n);
    for (int i = 0; i < n - 1; i++) {
        a[i] = i + 1;
        b[i] = i + 2;
    }
    for (int i = 0; i < n; i++) {
        s[i] = i * 1000000LL;
    }
    return {a, b, s};
}