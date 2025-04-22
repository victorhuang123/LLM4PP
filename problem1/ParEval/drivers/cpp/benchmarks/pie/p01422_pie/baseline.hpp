#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

double baseline(int n, const vector<int>& a, double u) {
    auto DFS = [&](int k, int m, double r, auto&& DFS) -> bool {
        int s = ceil(a[k] - a[k] * r);
        if (s == 0) s = 1;
        int e = ceil(a[k] + a[k] * r);
        for (int p = ((s - 1) / m + 1) * m; p < e; p += m)
            if (k == n - 1) return true;
            else if (DFS(k + 1, p, r, DFS)) return true;
        return false;
    };

    auto C = [&](double r) -> bool {
        return DFS(0, 1, r, DFS);
    };

    double l = 0.0;
    while (u - l > 1e-9) {
        double mid = (u + l) * 0.5;
        if (C(mid)) u = mid;
        else l = mid;
    }
    return u;
}

