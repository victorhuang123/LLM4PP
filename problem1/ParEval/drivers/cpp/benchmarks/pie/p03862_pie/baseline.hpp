#pragma once

#include <vector>

using namespace std;

long long baseline(long long n, long long x, vector<long long>& a) {
    long long t, ans = 0;
    if (a[0] > x) {
        t = a[0] - x;
        ans += t;
        a[0] -= t;
    }
    for (int i = 1; i < n; i++) {
        if (a[i] + a[i-1] > x) {
            t = a[i] + a[i-1] - x;
            ans += t;
            a[i] -= t;
        }
    }
    return ans;
}

vector<long long> generateInput(long long n, long long x) {
    vector<long long> a(n, x + 1);
    return a;
}