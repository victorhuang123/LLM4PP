#pragma once

#include <vector>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cmath>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>

using namespace std;

constexpr int MOD = 1000000007;
typedef long long LL;

vector<long long> baseline(int N, int K) {
    vector<long long> fact, fact_inv, inv;
    fact.resize(1e5 + 5);
    fact_inv.resize(1e5 + 5);
    inv.resize(1e5 + 5);
    fact[0] = fact[1] = 1;
    fact_inv[0] = fact_inv[1] = 1;
    inv[1] = 1;
    for (int i = 2; i < 1e5 + 5; i++) {
        fact[i] = fact[i - 1] * i % MOD;
        inv[i] = MOD - inv[MOD % i] * (MOD / i) % MOD;
        fact_inv[i] = fact_inv[i - 1] * inv[i] % MOD;
    }

    auto nCk = [&](int n, int k) -> long long {
        if (n < k) return 0;
        if (n < 0 || k < 0) return 0;
        return fact[n] * (fact_inv[k] * fact_inv[n - k] % MOD) % MOD;
    };

    vector<long long> result;
    for (int k = 1; k <= K; ++k) {
        result.push_back(nCk(N - K + 1, k) * nCk(K - 1, k - 1) % MOD);
    }
    return result;
}

vector<int> generate_input() {
    return {100000, 50000};
}