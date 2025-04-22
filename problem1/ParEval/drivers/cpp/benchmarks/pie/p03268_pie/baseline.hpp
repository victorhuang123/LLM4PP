#pragma once

#include <bits/stdc++.h>

using namespace std;

#define flash ios_base::sync_with_stdio(0); cin.tie(0)

long long baseline(long long n, long long k) {
    flash;
    long long cnt1 = 0, cnt2 = 0, ans = 0;

    for(int i = 1; i <= n; i++) {
        if(i % k == 0)
            cnt1++;
    }

    ans = cnt1 * cnt1 * cnt1;

    if(k % 2 == 0) {
        for(int i = 1; i <= n; i++) {
            if(i % k == k / 2)
                cnt2++;
        }
    }

    ans += cnt2 * cnt2 * cnt2;

    return ans;
}

vector<long long> generateInput() {
    return {1000000000, 2};
}