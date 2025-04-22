#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<long long> generateInput() {
    return {200005};
}

long long baseline(long long num) {
    const long long n = 200005;
    vector<long long> v(n, 0);
    vector<long long> prime;

    for (long long i = 3; i * i <= n; i += 2) {
        for (long long j = i * i; j <= n; j += (i + i)) {
            v[j - 1] = 1;
        }
    }

    prime.push_back(2);
    for (long long i = 3; i < n; i += 2) {
        if (v[i - 1] == 0) {
            prime.push_back(i);
        }
    }

    for (long long i = 0; i < n; i++) {
        if (prime[i] >= num) {
            return prime[i];
        }
    }
    return -1;
}