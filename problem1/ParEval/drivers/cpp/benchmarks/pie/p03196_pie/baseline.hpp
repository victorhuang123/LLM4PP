#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long l;

l baseline(l n, l k) {
    l o = 0, ans = 1;
    bool ok = 0;
    vector<bool> w(5000005, 0);

    if (n == 1) {
        return k;
    }

    for (int i = 2; ok == 0; i++) {
        if (i * i > k)
            break;
        if (w[i] == 1)
            continue;
        o = 1;
        for (int c = 0; c < n; c++) {
            o = o * i;
            if (o > k) {
                ok = 1;
                break;
            }
        }
        if (k % o == 0)
            ans = i;
        else
            for (l d = i; d < 5000005; d += i)
                w[d] = 1;
    }
    return ans;
}

vector<l> generateInput() {
    l n = 1000000;
    l k = 1000000000000LL;
    return {n, k};
}