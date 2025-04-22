#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> generateInput() {
    return {1, 1000000, 1000000, 10};
}

int baseline(int p, int q, int a, int n) {
    function<int(int,int,int,int,int)> dfs = [&](int denom, int numer, int prev, int product, int num) {
        int res = 0;
        if ((double)p/q - eps <= (double)numer/denom && (double)numer/denom <= (double)p/q + eps) ++res;
        if (num == 0) return res;

        {
            int tmp1 = denom * prev, tmp2 = numer * prev + denom * num;
            if ((double)tmp2 / tmp1 < (double)p / q) return 0;
        }

        if ((double)numer / denom > (double)p / q) return 0;

        int x = prev;
        while (true) {
            if (product * x > a) break;
            res += dfs(denom * x, numer * x + denom, x, product * x, num - 1);
            ++x;
        }
        return res;
    };

    return dfs(1, 0, 1, 1, n);
}