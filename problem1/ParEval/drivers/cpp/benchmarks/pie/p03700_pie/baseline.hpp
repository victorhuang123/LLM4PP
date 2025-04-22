#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

long long baseline(long long n, long long a, long long b, vector<long long>& h) {
    long long ans = 1e9;
    sort(h.begin(), h.end());
    long long left = 1, right = 1e9, mid, cnt = 0;
    while (right != left + 1) {
        mid = (right + left) / 2;
        cnt = 0;
        for (int i = 0; i < n; ++i) {
            long long temp = h[i] - b * mid;
            if (temp > 0) {
                cnt += ceil(1.0 * temp / (a - b));
            }
        }
        bool flg = cnt < mid;
        if (flg) {
            right = mid;
        } else {
            left = mid;
        }
    }
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        long long temp = h[i] - b * left;
        if (temp > 0) {
            cnt += ceil(1.0 * temp / (a - b));
        }
    }
    ans = min(ans, max(cnt, left));
    cnt = 0;
    for (int i = 0; i < n; ++i) {
        long long temp = h[i] - b * right;
        if (temp > 0) {
            cnt += ceil(1.0 * temp / (a - b));
        }
    }
    ans = min(ans, max(cnt, right));
    return ans;
}

vector<long long> generateInput(long long n) {
    vector<long long> h(n);
    for (long long i = 0; i < n; ++i) {
        h[i] = 1e9;
    }
    return h;
}