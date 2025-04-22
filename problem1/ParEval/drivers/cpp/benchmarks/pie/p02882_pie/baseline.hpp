#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<ll, ll> l_l;

typedef pair<int, int> i_i;

const long double PI = (acos(-1));

const long double EPS = 0.0000000001;

long double baseline(long double a, long double b, long double x) {
    auto f = [&](long double a, long double b, long double theta) {
        if(theta > PI / 2.0 - EPS) {
            return 0.0L;
        }
        long double ret;
        if(a * tan(theta) <= b) {
            ret = a * a * b - a * a * a * tan(theta) / 2.0;
        } else {
            ret = b * b / tan(theta) * a / 2.0;
        }
        return ret;
    };

    long double ok = PI / 2.0;
    long double ng = 0.0;
    for(int _ = 1; _ <= 100000; _++) {
        long double mid = (ok + ng) / 2.0;
        if(f(a, b, mid) < x) ok = mid;
        else ng = mid;
    }
    return ok / PI * 180;
}

vector<long double> generateInput() {
    vector<long double> input;
    input.push_back(1000000.0); // a
    input.push_back(1000000.0); // b
    input.push_back(500000000000.0); // x
    return input;
}