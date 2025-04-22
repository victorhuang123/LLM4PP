#pragma once

#include <bits/stdc++.h>

using namespace std;

double baseline(int n, int m, vector<pair<double, double>>& input) {
    vector<int> q(n + 1);
    struct node { double x, y, z; };
    vector<node> a(n + 1);
    int head = 1, tail = 0;
    double now = 0, ans = 0;

    for (int i = 1; i <= n; i++) {
        a[i].x = input[i-1].first;
        a[i].y = input[i-1].second;
        ans += a[i].x * a[i].y;
        a[i].z = now = now + a[i].y;

        for (; head <= tail && a[q[head]].z <= now - m; head++) {
            int k = q[head];
            ans -= a[k].x * a[k].y;
        }

        if (head <= tail) {
            int k = q[head];
            ans -= a[k].x * a[k].y;
            a[k].y = a[k].z - (now - m);
            ans += a[k].x * a[k].y;
        }

        for (; head <= tail && a[q[tail]].x > a[i].x; tail--) {
            int k = q[tail];
            a[i].x = (a[i].x * a[i].y + a[k].x * a[k].y) / (a[i].y + a[k].y);
            a[i].y += a[k].y;
        }

        q[++tail] = i;
    }

    return ans / m;
}

vector<pair<double, double>> generateInput(int n) {
    return vector<pair<double, double>>(n, {1.0, 1.0});
}