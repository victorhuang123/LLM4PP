
#include<bits/stdc++.h>
using namespace std;


long long baseline(long long r1, long long c1, long long r2, long long c2) {
    const long long mod = 1000000007;
    long long ans = 0;
    vector<pair<pair<long long, long long>, int>> params = {
        {{r2, c2}, 1},
        {{r2, c1 - 1}, -1},
        {{r1 - 1, c2}, -1},
        {{r1 - 1, c1 - 1}, 1}
    };

    for (auto &[rc, sign] : params) {
        long long r = rc.first;
        long long c = rc.second;

        long long y = 1;
        for (long long i = r + c + 2; i >= c + 2; --i) {
            y = (y * i) % mod;
        }

        long long x = 1;
        for (long long i = 2; i <= r + 1; ++i) {
            x = (x * i) % mod;
        }

        long long a = x, m = mod;
        long long old_r = a, r_euclid = m;
        long long old_s = 1, s = 0;
        long long old_t = 0, t = 1;

        while (r_euclid != 0) {
            long long quotient = old_r / r_euclid;
            long long temp = r_euclid;
            r_euclid = old_r - quotient * r_euclid;
            old_r = temp;

            temp = s;
            s = old_s - quotient * s;
            old_s = temp;

            temp = t;
            t = old_t - quotient * t;
            old_t = temp;
        }

        long long inv_x = (old_s % m + m) % m;
        long long term = (y * inv_x) % mod;
        term = (term - 1 + mod) % mod;

        ans = (ans + sign * term) % mod;
    }

    ans = (ans + mod) % mod;
    return ans;
}