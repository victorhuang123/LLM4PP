#pragma once

#include <bits/stdc++.h>

const int D = 4;
const int MODN = 1e9 + 7;

struct M {
    int d[D][D];
    M() {
        memset(d, 0, sizeof d);
    }
    M operator*(const M& other) const {
        M ret;
        for (int j = 0; j < D; ++j)
            for (int i = 0; i < D; ++i)
                for (int k = 0; k < D; ++k) {
                    ret.d[i][k] = (1LL * d[i][j] * other.d[j][k] + ret.d[i][k]) % MODN;
                }
        return ret;
    }
};

M pw(M x, int n) {
    M ret;
    for (int i = 0; i < D; ++i) ret.d[i][i] = 1;
    for (; n; n >>= 1, x = x * x)
        if (n & 1) ret = ret * x;
    return ret;
}

int baseline(int n, int m, const std::vector<int>& x) {
    M T, cur, Tb;
    for (int i = 0; i < D; ++i) cur.d[i][i] = 1;
    T.d[0][3] = 1;
    T.d[1][1] = T.d[1][3] = 1;
    T.d[2][1] = T.d[2][2] = T.d[2][3] = 1;
    T.d[3][1] = 1; T.d[3][2] = T.d[3][3] = 2;

    Tb.d[1][1] = 1;
    Tb.d[2][1] = Tb.d[2][2] = 1;
    Tb.d[3][1] = 1; Tb.d[3][2] = 2; Tb.d[3][3] = 1;

    int last = 0;
    for (int i = 0; i < m; ++i) {
        cur = pw(T, x[i] - last - 1) * cur;
        cur = Tb * cur;
        last = x[i];
    }

    cur = pw(T, n - last) * cur;
    int ans = 0;
    for (int i = 0; i < D; ++i)
        ans = (ans + cur.d[0][i]) % MODN;
    return ans;
}

std::vector<int> generateInput(int n, int m) {
    std::vector<int> x(m);
    for (int i = 0; i < m; ++i) {
        x[i] = rand() % n + 1;
    }
    std::sort(x.begin(), x.end());
    return x;
}