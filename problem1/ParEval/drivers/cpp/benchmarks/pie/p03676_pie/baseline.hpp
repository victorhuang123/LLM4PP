
#include <bits/stdc++.h>

using namespace std;


vector<long long> baseline(long long n, const vector<long long>& input) {
    const long long mod = 1e9 + 7;
    const long long N = 1e5 + 20;
    static vector<long long> fa(N), inv(N);
    static bool initialized = false;

    if (!initialized) {
        fa[0] = fa[1] = 1;
        inv[1] = 1;
        for (long long i = 2; i < N; ++i) {
            fa[i] = fa[i - 1] * i % mod;
            inv[i] = (mod - mod / i) * inv[mod % i] % mod;
        }
        inv[0] = 1;
        for (int i = 1; i < N; ++i) {
            inv[i] = inv[i] * inv[i - 1] % mod;
        }
        initialized = true;
    }

    map<long long, int> q;
    long long p = 0;
    for (int i = 1; i <= n + 1; ++i) {
        auto it = q.find(input[i]);
        if (it == q.end()) {
            q[input[i]] = i;
        } else {
            p = i;
        }
    }

    vector<long long> result(n + 1);
    for (int i = 0; i <= n; ++i) {
        long long comb1 = 0, comb2 = 0;
        long long k1 = i + 1;
        if (k1 <= n + 1) {
            comb1 = ((fa[n + 1] * inv[k1]) % mod) * inv[n + 1 - k1] % mod;
        }

        long long m = n - p + q.at(input[p]);
        if (i <= m) {
            comb2 = ((fa[m] * inv[i]) % mod) * inv[m - i] % mod;
        }

        long long ans = (comb1 - comb2) % mod;
        if (ans < 0) ans += mod;
        result[i] = ans;
    }

    return result;
}

