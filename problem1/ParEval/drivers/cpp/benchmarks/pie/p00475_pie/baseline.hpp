#pragma once

#include <algorithm>
#include <utility>
#include <climits>
#include <vector>

using namespace std;

typedef pair<int,int> P;

int baseline(int n, const vector<P>& za) {
    int lx = INT_MAX, ly = INT_MAX, rx = INT_MIN, ry = INT_MIN;

    for(int i = 0; i < n; i++) {
        lx = min(lx, za[i].first);
        rx = max(rx, za[i].first);
        ly = min(ly, za[i].second);
        ry = max(ry, za[i].second);
    }

    int ret1 = 0, ret2 = 0;
    for(int i = 0; i < n; i++) {
        ret1 = max(ret1, min(max(za[i].first - lx, za[i].second - ly), max(rx - za[i].first, ry - za[i].second)));
        ret2 = max(ret2, min(max(za[i].first - lx, ry - za[i].second), max(rx - za[i].first, za[i].second - ly)));
    }

    return min(ret1, ret2);
}

vector<P> generateInput(int n) {
    vector<P> za(n);
    for(int i = 0; i < n; i++) {
        za[i] = make_pair(i, i);
    }
    return za;
}