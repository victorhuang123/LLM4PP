#pragma once

#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

typedef long long ll;

ll baseline(int N, const vector<int>& x, const vector<int>& s) {
    ll S = 0, mi = LLONG_MAX, ans = 0;
    for (int i = 0; i < N; ++i) {
        ll prev = S, cur = S + s[i];
        prev -= x[i]; cur -= x[i];
        mi = min(mi, prev);
        ans = max(ans, cur - mi);
        S += s[i];
    }
    return ans;
}

vector<int> generateInput(int N) {
    vector<int> x(N), s(N);
    for (int i = 0; i < N; ++i) {
        x[i] = i + 1;
        s[i] = (i + 1) * 100;
    }
    return x, s;
}