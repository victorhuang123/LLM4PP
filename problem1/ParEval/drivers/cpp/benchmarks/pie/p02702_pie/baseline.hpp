
#include <bits/stdc++.h>
using namespace std;

long long baseline(const string& S) {
    const long long MOD = 1000000009LL;
    const long long inv2 = 500000005LL;
    int N = S.size();
    vector<long long> count(2019, 0LL);
    long long num = 0LL;
    long long keta = 1LL;

    for (int i = N - 1; i >= 0; --i) {
        num = (num + (S[i] - '0') * keta) % 2019;
        count[num]++;
        keta = (keta * 10) % 2019;
    }

    count[0]++;
    long long ans = 0;
    for (int i = 0; i < 2019; ++i) {
        long long cnt = count[i];
        ans = (ans + (cnt * (cnt - 1) % MOD) * inv2 % MOD) % MOD;
    }

    return ans;
}

