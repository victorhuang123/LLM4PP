#pragma once

#include <cmath>
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

double baseline(int n, const vector<double>& x, const vector<double>& y) {
    vector<pair<double, double>> p1(n), p2(n);

    for(int i = 0; i < n; i++) {
        p1[i] = make_pair(x[i], y[i]);
    }

    for(int i = 0; i < n; i++) {
        p2[i] = make_pair(y[i], x[i]);
    }

    sort(p1.begin(), p1.end());
    sort(p2.begin(), p2.end());

    double sqr_ans = 100000000.0;

    const int loops = 125;

    for(int i = 0; i < n - 1; i++) {
        int r = min(loops, n - i - 1);

        for(int j = 1; j <= r; j++) {
            double distance_ = (p1[i + j].first - p1[i].first) * (p1[i + j].first - p1[i].first) + (p1[i + j].second - p1[i].second) * (p1[i + j].second - p1[i].second);
            sqr_ans = min(distance_, sqr_ans);
        }
    }

    for(int i = 0; i < n - 1; i++) {
        int r = min(loops, n - i - 1);

        for(int j = 1; j <= r; j++) {
            double distance_ = (p2[i + j].first - p2[i].first) * (p2[i + j].first - p2[i].first) + (p2[i + j].second - p2[i].second) * (p2[i + j].second - p2[i].second);
            sqr_ans = min(distance_, sqr_ans);
        }
    }

    return sqrt(sqr_ans);
}

vector<double> generateInput(int n) {
    vector<double> x(n), y(n);
    for(int i = 0; i < n; i++) {
        x[i] = static_cast<double>(rand()) / RAND_MAX * 100000.0;
        y[i] = static_cast<double>(rand()) / RAND_MAX * 100000.0;
    }
    return {x, y};
}