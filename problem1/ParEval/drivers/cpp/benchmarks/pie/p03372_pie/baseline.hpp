#pragma once

#include <vector>
#include <algorithm>
#define LL long long

struct Node {
    LL p, v;
    bool operator < (const Node &a) const {
        return p < a.p;
    }
};

LL baseline(int n, LL C, std::vector<Node>& T) {
    std::vector<LL> A1(n + 2), A2(n + 2), B1(n + 2), B2(n + 2), p(n + 2), v(n + 2);
    LL ans = 0;

    std::sort(T.begin() + 1, T.begin() + n + 1);
    for (int i = 1; i <= n; i++) {
        p[i] = T[i].p;
        v[i] = T[i].v;
    }
    p[n + 1] = C;

    for (int i = 1; i <= n; i++) {
        A1[i] = A1[i - 1] + v[i] - (p[i] - p[i - 1]);
        ans = std::max(A1[i], ans);
        B1[i] = A1[i] - p[i];
        if (i > 1) B1[i] = std::max(B1[i], B1[i - 1]);
    }

    for (int i = n; i >= 1; i--) {
        A2[i] = A2[i + 1] + v[i] - (p[i + 1] - p[i]);
        ans = std::max(ans, A2[i]);
        B2[i] = A2[i] - (C - p[i]);
        if (i < n) B2[i] = std::max(B2[i], B2[i + 1]);
    }

    for (int i = 1; i < n; i++) ans = std::max(ans, A1[i] + B2[i + 1]);
    for (int i = 2; i <= n; i++) ans = std::max(ans, A2[i] + B1[i - 1]);

    return ans;
}

std::vector<Node> generateInput(int n, LL C) {
    std::vector<Node> T(n + 1);
    for (int i = 1; i <= n; i++) {
        T[i].p = i * 1000;
        T[i].v = i * 100;
    }
    return T;
}