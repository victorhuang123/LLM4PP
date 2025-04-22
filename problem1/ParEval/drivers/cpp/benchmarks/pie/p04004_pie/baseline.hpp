#pragma once

#include<vector>

using namespace std;

const long long mod = 1e9 + 7;

long long baseline(int n, int m, int k) {
    vector<long long> jc(n + m + k + 1), _jc(n + m + k + 1);
    jc[0] = 1;
    _jc[0] = 1;
    for (int i = 1; i <= n + m + k; i++) {
        jc[i] = jc[i - 1] * i % mod;
        long long pow_val = 1, base = jc[i], exp = mod - 2;
        while (exp > 0) {
            if (exp & 1) pow_val = pow_val * base % mod;
            base = base * base % mod;
            exp /= 2;
        }
        _jc[i] = pow_val;
    }
    auto C = [&](int n, int m) {
        return jc[n] * _jc[m] % mod * _jc[n - m] % mod;
    };
    long long tmp = 1, ans = 0;
    for (int i = 0; i <= m + k; i++) {
        ans = (ans + C(n + i - 1, i) * tmp % mod * (i < m + k ? 3 : 1) % mod) % mod;
        tmp *= 2;
        if (i + 1 > k) tmp -= C(i, i - k);
        if (i + 1 > m) tmp -= C(i, m);
        tmp += 2 * mod;
        tmp %= mod;
    }
    return ans;
}

vector<int> generate_input() {
    return {1000000, 1000000, 1000000};
}