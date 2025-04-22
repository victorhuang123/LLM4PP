#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int n, const vector<int>& a) {
    int B = 0, W = 0;
    vector<int> s(n + 1, 0);

    for (int i = 1; i <= n; ++i) {
        if (i & 1) {
            B += a[i];
            s[i] = s[i-1] + a[i];
        } else {
            W += a[i];
            s[i] = s[i-1] - a[i];
        }
    }

    if (~n & 1) {
        return max(B, W);
    }

    int l = 0, r = B, re = -1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        bool valid = false;
        int mn = 0;
        if (s[n] >= mid) valid = true;
        for (int i = 2; i <= n && !valid; ++i) {
            if (s[i-1] - mn >= mid) {
                if (s[n] - s[i] >= mid) valid = true;
                mn = min(mn, s[i]);
            }
        }
        if (valid) {
            l = mid + 1;
            re = mid;
        } else {
            r = mid - 1;
        }
    }

    return max(B, W + re);
}

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) {
        a[i] = rand() % 1000000 + 1;
    }
    return a;
}