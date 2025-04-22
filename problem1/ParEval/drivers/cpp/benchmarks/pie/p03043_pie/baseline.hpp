#pragma once

#include <vector>
#include <cmath>

using namespace std;
using ll = long long;
typedef long double ld;

ld baseline(int n, int m) {
    const long double eps = 1e-12;
    const int maxn = (int)1e5 + 10;
    vector<ld> p(maxn);
    
    p[0] = 1;
    for (int i = 1; i < maxn; i++) {
        p[i] = p[i - 1] * 0.5;
    }

    ld sum = 0;
    for (ll i = 1; i <= n; i++) {
        ll cnt = 0, r = i;
        while (r < m) r *= 2, cnt++;
        sum += (ld)((1.0 / n) * p[cnt]);
    }
    return sum;
}

vector<int> generateInput() {
    return {100000, 1000000000};
}