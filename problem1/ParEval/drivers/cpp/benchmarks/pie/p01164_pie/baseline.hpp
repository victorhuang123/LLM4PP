#pragma once

#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

inline int pack(int p, int ps, int n) {
    return (p << n) | ps;
}

int baseline(int n, const string& sa, const string& sb) {
    auto conv = [n](const string& s) {
        int r = 0;
        for (int i = 0; i < n; i++) {
            r = (r << 1) + (s[i] == 'W' ? 1 : 0);
        }
        return r;
    };

    int a = conv(sa);
    int b = conv(sb);

    vector<int> ds(n << n, 100000000);
    priority_queue<pair<int, int>> que;

    for (int i = 0; i < n; i++) {
        int v = pack(i, a, n);
        ds[v] = 0;
        que.push(make_pair(-ds[v], v));
    }

    vector<bool> done(n, false);
    int rest = n;

    while (que.size() > 0) {
        auto dv = que.top(); que.pop();
        const int v = dv.second;
        const int d = -dv.first;
        const int p = v >> n;
        const int s = v & ((1 << n) - 1);

        if (s == b) {
            if (!done[p]) {
                done[p] = true;
                rest--;
            }
            if (rest == 0) {
                int e = d;
                for (int i = 0; i < n; i++) {
                    e = min(e, ds[pack(i, b, n)]);
                }
                return e;
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if ((((s >> i) ^ (s >> j)) & 1) == 0) continue;
                const int c = abs(i - p) + abs(j - i);
                const int u = pack(j, s ^ (1 << i) ^ (1 << j), n);
                if (ds[u] > d + c) {
                    ds[u] = d + c;
                    que.push(make_pair(-ds[u], u));
                }
            }
        }
    }
    return -1; // If no solution is found
}

vector<string> generateInput(int n) {
    string sa(n, 'W');
    string sb(n, 'B');
    return {sa, sb};
}