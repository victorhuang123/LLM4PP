#pragma once

#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

#define pi 3.141592653589793238
#define int long long

using namespace __gnu_pbds;
using namespace std;

template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

bool baseline(int n, int m, int k, int x, int y, const string& s, const string& t) {
    int xx = 0;
    for (int i = 0; i < k; i++) {
        if (s[i] == 'L')
            xx++;
        if (xx >= y) {
            return false;
        }
        if (t[i] == 'R') {
            if (xx <= 0) {
                if (abs(xx) + y + 1 > m)
                    continue;
            }
            xx--;
        }
    }

    xx = 0;
    for (int i = 0; i < k; i++) {
        if (s[i] == 'R')
            xx++;
        if (xx + y > m) {
            return false;
        }
        if (t[i] == 'L') {
            if (xx <= 0) {
                if (abs(xx) + 1 >= y)
                    continue;
            }
            xx--;
        }
    }

    xx = 0;
    for (int i = 0; i < k; i++) {
        if (s[i] == 'U')
            xx++;
        if (xx >= x) {
            return false;
        }
        if (t[i] == 'D') {
            if (xx <= 0) {
                if (abs(xx) + x + 1 > n)
                    continue;
            }
            xx--;
        }
    }

    xx = 0;
    for (int i = 0; i < k; i++) {
        if (s[i] == 'D')
            xx++;
        if (xx + x > n) {
            return false;
        }
        if (t[i] == 'U') {
            if (xx <= 0) {
                if (abs(xx) + 1 >= x)
                    continue;
            }
            xx--;
        }
    }

    return true;
}

vector<int> generate_input() {
    int n = 1e9, m = 1e9, k = 1e6, x = 1e9, y = 1e9;
    string s(k, 'L'), t(k, 'R');
    return {n, m, k, x, y, s, t};
}