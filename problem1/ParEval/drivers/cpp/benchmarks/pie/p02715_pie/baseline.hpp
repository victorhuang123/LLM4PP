
#include<vector>
#include<algorithm>

using namespace std;


long long baseline(long long n, long long k) {
    const long long MOD = 1e9 + 7;
    vector<long long> pri, jud(k + 1, 0), phi(k + 1, 0);
    phi[1] = 1;

    for (long long i = 2; i <= k; ++i) {
        if (!jud[i]) {
            pri.push_back(i);
            phi[i] = (i - 1) % MOD;
        }
        for (long long j = 0; j < pri.size() && i * pri[j] <= k; ++j) {
            jud[i * pri[j]] = 1;
            if (i % pri[j] == 0) {
                phi[i * pri[j]] = (phi[i] * pri[j]) % MOD;
                break;
            }
            phi[i * pri[j]] = (phi[i] * phi[pri[j]]) % MOD;
        }
    }

    long long res = 0;
    for (long long i = 1; i <= k; ++i) {
        long long base = k / i;
        long long exponent = n;
        long long power = 1, current = base % MOD;
        while (exponent) {
            if (exponent & 1) power = (power * current) % MOD;
            current = (current * current) % MOD;
            exponent >>= 1;
        }
        res = (res + power * phi[i]) % MOD;
    }
    return (res % MOD + MOD) % MOD;
}

