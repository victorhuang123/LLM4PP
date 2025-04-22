#pragma once

#include <bits/stdc++.h>

using namespace std;

using VI = vector<int>;

#define ALL(a)  begin((a)),end((a))
#define SZ(a) int((a).size())
#define FOR(i, s, e) for (int(i) = (s); (i) < (e); (i)++)

int baseline(int N, VI& a) {
    VI cnt(100005);
    FOR(i, 0, N) {
        cnt[a[i]]++;
    }
    VI pq;
    FOR(i, 0, 100005) {
        if (cnt[i]) pq.push_back(cnt[i]);
    }
    int even = 0;
    FOR(i, 0, SZ(pq)) {
        if (pq[i] % 2 == 0) even++;
    }
    int ans = SZ(pq);
    if (even % 2 == 1) ans--;
    return ans;
}

VI generateInput(int N) {
    VI a(N);
    FOR(i, 0, N) {
        a[i] = rand() % 100000;
    }
    return a;
}