

#include <bits/stdc++.h>
using namespace std;

double baseline(int n, double d0, double d) {
    double ans = 0.0;
    n = n << 1;
    d0 -= d;

    for( ; n >= 2; n -= 2 ) {
        ans += d0 + d * (n + 1) / 2.0;
        double nd0 = d0 + (2 * d0 + 3 * d) / n;
        double nd = d + (4 * d) / n;
        d0 = nd0;
        d = nd;
    }

    return ans;
}
