#pragma once

#include <bits/stdc++.h>

using namespace std;

#define rep(i,a,b) for(int i=a;i<=b;i++)
#define dep(i,a,b) for(int i=a;i>=b;i--)
#define N 500005
#define inf 666666666

vector<int> generate_input() {
    int n = N - 5;
    int k = 100;
    vector<int> p(n + 1);
    rep(i, 1, n) p[i] = i;
    random_shuffle(p.begin() + 1, p.end());
    return p;
}

vector<int> baseline(int n, int k, const vector<int>& p) {
    vector<int> in(n + 1, 0), pos(n + 1, 0), ans(n + 1, 0);
    vector<int> head(n + 1, 0), to(n << 1, 0), nxt(n << 1, 0);
    int cnt = 0, tot = 0;
    priority_queue<int> q;
    vector<int> t(n << 2, inf);

    auto add = [&](int u, int v) {
        cnt++;
        to[cnt] = v;
        nxt[cnt] = head[u];
        head[u] = cnt;
    };

    auto change = [&](int id, int l, int r, int p, int d) {
        if (l == r) {
            t[id] = d;
            return;
        }
        int mid = (l + r) >> 1;
        if (p <= mid) change(id << 1, l, mid, p, d);
        else change(id << 1 | 1, mid + 1, r, p, d);
        t[id] = min(t[id << 1], t[id << 1 | 1]);
    };

    auto query = [&](int id, int L, int R, int l, int r) {
        if (t[id] >= N) return inf;
        if (l == L && r == R) return t[id];
        int Mid = (L + R) >> 1;
        if (r <= Mid) return query(id << 1, L, Mid, l, r);
        else if (l > Mid) return query(id << 1 | 1, Mid + 1, R, l, r);
        else return min(query(id << 1, L, Mid, l, Mid), query(id << 1 | 1, Mid + 1, R, Mid + 1, r));
    };

    dep(i, n, 1) {
        int pos1 = query(1, 1, n, p[i], min(n, p[i] + k - 1));
        if (pos1 != inf) {
            add(p[i], p[pos1]);
            in[p[pos1]]++;
        }
        int pos2 = query(1, 1, n, max(1, p[i] - k + 1), p[i]);
        if (pos2 != inf) {
            add(p[i], p[pos2]);
            in[p[pos2]]++;
        }
        change(1, 1, n, p[i], i);
    }
    rep(i, 1, n) if (!in[i]) q.push(-i);
    while (!q.empty()) {
        int now = -q.top();
        ans[now] = ++tot;
        q.pop();
        for (int i = head[now]; i; i = nxt[i]) {
            int v = to[i];
            --in[v];
            if (!in[v]) q.push(-v);
        }
    }
    return ans;
}