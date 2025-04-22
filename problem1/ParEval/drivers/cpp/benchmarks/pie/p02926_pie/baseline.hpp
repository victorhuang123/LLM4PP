#pragma once

#include<bits/stdc++.h>

using namespace std;

struct uzi {
    int a, b;
    bool operator <(const uzi & t)const {
        return atan2(a, b) < atan2(t.a, t.b);
    }
};

double baseline(int n, vector<uzi>& p) {
    sort(p.begin(), p.end());
    double ans = 0;
    for (int i = 1; i <= n; i++) {
        long long x = 0, y = 0;
        for (int j = 0; j < n; j++) {
            x += p[((i + j) % n) == 0 ? n - 1 : ((i + j) % n) - 1].a;
            y += p[((i + j) % n) == 0 ? n - 1 : ((i + j) % n) - 1].b;
            ans = max(ans, sqrt(x * x + y * y));
        }
    }
    return ans;
}

vector<uzi> generateInput(int n) {
    vector<uzi> p(n);
    for (int i = 0; i < n; i++) {
        p[i] = {rand() % 10000, rand() % 10000};
    }
    return p;
}