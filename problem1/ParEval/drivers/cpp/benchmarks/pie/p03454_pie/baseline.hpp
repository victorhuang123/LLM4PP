#pragma once

#include <vector>
#include <algorithm>

using namespace std;

const int mod = 1'000'000'007;

int baseline(int s) {
    auto add = [](int &a, int b) {
        a += b;
        if (a >= mod) a -= mod;
    };

    auto mul = [](int a, int b) {
        return (int)((long long)a * b % mod);
    };

    auto pw = [&](int a, int b) {
        int res = 1;
        while (b > 0) {
            if (b % 2 == 1) res = mul(res, a);
            a = mul(a, a);
            b /= 2;
        }
        return res;
    };

    auto get = [&](int b) {
        int res = pw(10, b);
        add(res, mod - pw(10, b - 1));
        return res;
    };

    int ans = 0;
    for (int i = 1; i <= s; ++i) {
        if (s % i == 0) {
            int cnt = get(i);
            if (i >= 9 || cnt >= s / i) {
                add(ans, cnt);
                add(ans, mod - s / i + 1);
            }
        }
    }
    for (int i = 1; i <= 8; ++i) {
        long long v = 0;
        for (int j = i + 1; j <= 9; ++j) {
            for (int k = 1; k <= get(i); ++k) {
                if (v + i * k >= s) break;
                if ((s - v - i * k) % j == 0 && (s - v - i * k) / j <= get(j)) {
                    add(ans, 1);
                }
            }
            v += j * get(j);
            if (v >= s) break;
        }
    }
    for (int i = 9; i < s; ++i) {
        int v = s / (i + 1);
        if (s % (i + 1) == 0) --v;
        int r = s % i;
        if (v >= r) {
            add(ans, (v - r) / i + (r != 0));
        }
    }
    return ans;
}

vector<int> generateInput() {
    return {1000000};  // Example input to maximize problem scale
}