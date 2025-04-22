#pragma once

#include <vector>
#include <algorithm>
#include <climits>
#include <cstring>

using namespace std;

typedef long long ll;

int baseline(int n, int x, int D, vector<ll>& m, vector<int>& p) {
    vector<int> v(n + 1, 1), id(n + 1);
    for (int i = 1; i <= n; ++i) id[i] = i;
    for (int i = n; i > 1; --i) {
        m[p[i]] += m[i];
        v[p[i]] += v[i];
    }

    vector<ll> f(n * n * n + 1, LLONG_MAX / 2);
    f[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int lim = 1, ret = (i == 1) ? n : min(n, D);
        while (ret >= lim) {
            ret -= lim;
            for (int j = n * n * n; j >= lim * v[i]; --j) {
                f[j] = min(f[j], f[j - lim * v[i]] + m[i] * lim);
            }
            lim <<= 1;
        }
        if (ret > 0) {
            for (int j = n * n * n; j >= ret * v[i]; --j) {
                f[j] = min(f[j], f[j - ret * v[i]] + m[i] * ret);
            }
        }
    }

    auto cmp = [&](int x, int y) {
        return m[y] * v[x] > m[x] * v[y];
    };
    sort(id.begin() + 1, id.end(), cmp);

    int ans = 0;
    for (int i = 0; i <= n * n * n; ++i) {
        if (f[i] <= x) {
            int res = x - f[i], sum = i;
            for (int j = 1; j <= n; ++j) {
                int del = (id[j] == 1) ? res / m[1] : min(max(0, D - n), (int)(res / m[id[j]]));
                sum += v[id[j]] * del;
                res -= del * m[id[j]];
            }
            ans = max(ans, sum);
        }
    }
    return ans;
}

vector<ll> generateInput(int n) {
    vector<ll> m(n + 1);
    for (int i = 2; i <= n; ++i) {
        m[i] = rand() % 1000000 + 1;
    }
    return m;
}

vector<int> generateP(int n) {
    vector<int> p(n + 1);
    for (int i = 2; i <= n; ++i) {
        p[i] = rand() % (i - 1) + 1;
    }
    return p;
}