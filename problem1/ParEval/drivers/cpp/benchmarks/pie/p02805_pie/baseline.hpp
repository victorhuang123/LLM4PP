#pragma once

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define iiii tuple<int, int, int, int>
#define iii tuple<int, int, int>
#define ii pair<int, int>
#define dd pair<double, double>
#define fi first
#define vi vector<int>
#define vvi vector<vector<int>>
#define se second

using namespace std;
using namespace __gnu_pbds;

template <typename T>
using ordered_set =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int M = 1e3;
double e = 1e-8;

double baseline(vector<ii>& a) {
    int cnt = 1000;
    double L = 1000, x = 0, y = 0;

    auto f = [&](double x, double y) {
        double res = 0;
        for (auto& i : a)
            res = max(res, (i.fi - x) * (i.fi - x) + (i.se - y) * (i.se - y));
        return sqrt(res);
    };

    auto dx = [&](double x, double y) {
        return (f(x + e, y) - f(x - e, y)) / e;
    };

    auto dy = [&](double x, double y) {
        return (f(x, y + e) - f(x, y - e)) / e;
    };

    auto test = [&](double L, double x, double y) {
        return f(x, y) > f(x - dx(x, y) * L, y - dy(x, y) * L);
    };

    auto cal_L = [&](double x, double y, double tdx, double tdy) {
        double lef = 0, rig = 1000;
        int cnt = 100;
        while (cnt--) {
            double l1 = (lef + lef + rig) / 3;
            double l2 = (lef + rig + rig) / 3;
            if (f(x - tdx * l1, y - tdy * l1) > f(x - tdx * l2, y - tdy * l2))
                lef = l1;
            else
                rig = l2;
        }
        return lef;
    };

    while (cnt--) {
        double tdx = dx(x, y), tdy = dy(x, y);
        L = cal_L(x, y, tdx, tdy);
        x -= tdx * L;
        y -= tdy * L;
    }
    return f(x, y);
}

vector<ii> generate_input() {
    vector<ii> a(M);
    for (int i = 0; i < M; ++i) {
        a[i] = {rand() % 10000, rand() % 10000};
    }
    return a;
}