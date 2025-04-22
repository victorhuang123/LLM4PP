#pragma once

#include<vector>
#include<algorithm>

#define DIV 100000

using namespace std;

long long baseline(long long n, long long m, vector<long long>& d, vector<long long>& k) {
    vector<long long> S(n);
    long long t = 0;
    long long ans = 0;
    S[0] = 0;

    for (int i = 1; i < n; i++) {
        S[i] = S[i - 1] + d[i - 1];
    }

    for (int i = 0; i < m; i++) {
        ans += abs(S[t] - S[t + k[i]]);
        ans = ans % DIV;
        t += k[i];
    }

    return ans;
}

vector<long long> generateInput(long long n, long long m) {
    vector<long long> d(n - 1);
    vector<long long> k(m);

    for (long long i = 0; i < n - 1; i++) {
        d[i] = rand() % 100000;
    }

    for (long long i = 0; i < m; i++) {
        k[i] = rand() % (n - 1) + 1;
    }

    return d, k;
}