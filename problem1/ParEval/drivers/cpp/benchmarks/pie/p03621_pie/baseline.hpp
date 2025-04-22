#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

static_assert(sizeof(long) >= 8, "sizeof(long) >= 8");

constexpr int mod = 998244353;

int baseline(const vector<char>& a, const vector<char>& b) {
    vector<long> fac(100001), inv(100001);
    vector<int> dp(10001);

    fac[0] = 1;
    for (int i = 1; i <= 100000; i++)
        fac[i] = fac[i - 1] * i % mod;

    inv[100000] = 812950533;
    for (int i = 100000; i >= 1; i--)
        inv[i - 1] = inv[i] * i % mod;

    int x = 0, y = 0;
    for (size_t i = 0; i < a.size(); i++)
        if (a[i] == '1')
            (b[i] == '0' ? x : y)++;

    dp[0] = 1;
    for (int i = 1; i <= x; i++)
        for (int j = 1; j <= y; j++)
            dp[j] = (dp[j] + (long) i * dp[j - 1]) % mod;

    long ans = 0;
    for (int i = 0; i <= y; i++)
        ans = (ans + dp[i] * inv[x + i]) % mod;

    return ans * fac[x] % mod * fac[x] % mod * fac[y] % mod * fac[x + y] % mod;
}

vector<char> generateInput(size_t size) {
    vector<char> input(size);
    for (size_t i = 0; i < size; i++) {
        input[i] = (i % 2 == 0) ? '1' : '0';
    }
    return input;
}