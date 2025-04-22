#pragma once

#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

using ll = long long int;

template<typename T> void chmax(T &a, T b) {a = max(a, b);}
template<typename T> void chmin(T &a, T b) {a = min(a, b);}
template<typename T> void chadd(T &a, T b) {a = a + b;}

const int INF = 1001001001;
const ll LONGINF = 1001001001001001LL;
const ll MOD = 1000000007LL;

template<typename T>
class Combination {
public:
    vector<T> fact, inv_fact;
    Combination(int n) {
        fact.resize(n + 1);
        inv_fact.resize(n + 1);
        fact[0] = 1;
        for (int i = 1; i <= n; i++) {
            fact[i] = fact[i - 1] * i;
        }
        inv_fact[n] = 1 / fact[n];
        for (int i = n - 1; i >= 0; i--) {
            inv_fact[i] = inv_fact[i + 1] * (i + 1);
        }
    }
    T H(int n, int k) {
        if (k < 0 || n < 0) return 0;
        if (n == 0 && k == 0) return 1;
        return fact[n + k - 1] * inv_fact[k] * inv_fact[n - 1];
    }
};

template<typename T>
T baseline(int N, int A, int B, int C) {
    if (B % 2 == 1) {
        return 0;
    }

    Combination<T> comb(10010);
    int q = B / 2;
    T ans(0);

    for (int x = 0; x <= C; x++) {
        for (int r = 0; r <= min(A, C); r++) {
            if ((C - x - r) < 0 || (C - x - r) % 3 != 0) continue;

            int p = A - r;
            int s = (C - x - r) / 3;

            T mul(1);
            mul *= comb.H(q, x);
            mul *= comb.H(q + 1, r);
            mul *= comb.H(q + 1 + r, s);
            mul *= comb.H(q + 1 + r + s, p);
            ans += mul;
        }
    }

    return ans;
}

vector<int> generate_input() {
    return {10000, 5000, 10000, 10000};
}