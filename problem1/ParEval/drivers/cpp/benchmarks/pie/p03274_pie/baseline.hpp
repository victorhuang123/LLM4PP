#pragma once

#include <bits/stdc++.h>

#define LL long long

using namespace std;

const int N = 1e5;

LL baseline(int n, int k, vector<LL>& a) {
    int cnt0 = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == 0) cnt0++;
    }

    if (k == 1 && cnt0) {
        return 0;
    }

    if (cnt0 == 0) {
        a.push_back(0);
        n++;
    }

    sort(a.begin(), a.end());

    int idx = 0;
    for (int i = 0; i < n; i++) if (a[i] == 0) idx = i;

    LL ans = 1e18;
    for (int i = 0; i < n; i++) {
        LL temp = 0;
        int cnt = 0;
        temp = temp + abs(a[idx] - a[i]);
        cnt += abs(idx - i);
        if (cnt0) cnt++;
        if (cnt > k) continue;
        if (cnt == k) {
            ans = min(ans, temp);
            continue;
        }
        if (i < idx) {
            if (idx + k - cnt < n) {
                temp = temp + 2 * abs(a[idx + k - cnt] - a[idx]);
                ans = min(ans, temp);
            } else continue;
        } else {
            if (idx - (k - cnt) >= 0) {
                temp = temp + 2 * abs(a[idx] - a[idx - (k - cnt)]);
                ans = min(ans, temp);
            }
        }
    }
    return ans;
}

vector<LL> generateInput(int n) {
    vector<LL> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = rand() % 1000000;
    }
    return a;
}