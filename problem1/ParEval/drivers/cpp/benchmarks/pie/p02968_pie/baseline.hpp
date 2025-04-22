#pragma once

#include<vector>
#include<algorithm>
#include<cmath>

struct dat {
    int x, y, id;
    dat() {}
    dat(int x, int y, int id) : x(x), y(y), id(id) {}
};

inline bool cmp(const dat& x, const dat& y) {
    if (x.x != y.x) return x.x < y.x;
    return x.y < y.y;
}

inline long long add(long long x, long long y, int mod) {
    return x + y >= mod ? x + y - mod : x + y;
}

inline long long sub(long long x, long long y, int mod) {
    return x - y < 0 ? x - y + mod : x - y;
}

long long baseline(int n, int mod) {
    int cnt = 0;
    long long ans = 0ll;
    std::vector<std::vector<long long>> f(2 * n + 1, std::vector<long long>(n + 1, 0));
    std::vector<dat> a(2 * n + 1);

    for (int k = 0; k < 2 * n; k++) {
        int l = std::max(0, (int)std::ceil(std::sqrt(n * n - k * k))), r = std::min(2 * n - 1, (int)std::sqrt(n * n * 4 - k * k));
        if (k < n) a[++cnt] = dat(l - 1, r, k);
        else a[++cnt] = dat(r, 0, k);
    }

    std::sort(a.begin() + 1, a.begin() + 1 + cnt, cmp);

    for (int k = 0; k <= n; k++) {
        for (auto& row : f) std::fill(row.begin(), row.end(), 0);
        f[0][0] = 1ll;
        int x = 0;
        for (int i = 1; i <= cnt; i++) {
            for (int j = 0; j <= k; j++) {
                if (a[i].id < n) {
                    if (a[i].x + 1 - x - (j - 1) > 0 && j)
                        f[i][j] = add(f[i][j], f[i - 1][j - 1] * (a[i].x + 1 - x - (j - 1)) % mod, mod);
                    if (a[i].y + 1 - k - n - (i - 1 - x - j) > 0)
                        f[i][j] = add(f[i][j], f[i - 1][j] * (a[i].y + 1 - k - n - (i - 1 - x - j)) % mod, mod);
                } else {
                    if (a[i].x + 1 - x - j > 0)
                        f[i][j] = f[i - 1][j] * (a[i].x + 1 - x - j) % mod;
                }
            }
            if (a[i].id >= n) x++;
        }
        if (k & 1) ans = sub(ans, f[cnt][k], mod);
        else ans = add(ans, f[cnt][k], mod);
    }
    return ans;
}

std::pair<int, int> generateInput() {
    return {500, 1000000007};
}