#pragma once

#include <vector>
#include <complex>
#include <algorithm>
#include <cmath>

using namespace std;

typedef complex<double> P;
const double EPS = 1e-10;

struct C {
    P p;
    double r;

    C() : p(P(0, 0)), r(0) {}

    C(const P& p, double r) : p(p), r(r) {}

    bool in(P t) {
        return norm(p - t) < r * r + EPS;
    }

    bool in(C t) {
        return abs(p - t.p) + t.r < r + EPS;
    }
};

bool check(double h, int n, const vector<double>& l, vector<C>& c) {
    for (int i = 0; i < n; i++) {
        if (l[i] * l[i] - h * h < EPS) return false;
        c[i].r = sqrt(l[i] * l[i] - h * h);
    }

    vector<P> cs;
    for (int i = 0; i < n; i++) {
        cs.push_back(c[i].p);
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            C c1 = c[i], c2 = c[j];
            if (abs(c1.p - c2.p) > c1.r + c2.r) return false;
            if (c1.in(c2) || c2.in(c1)) continue;

            P v = c2.p - c1.p;
            double t = (c1.r * c1.r + norm(v) - c2.r * c2.r) / (2 * abs(v));
            double theta = acos(t / c1.r);
            P b[2];
            b[0] = c1.p + v / abs(v) * c1.r * polar(1.0, theta);
            b[1] = c1.p + v / abs(v) * c1.r * polar(1.0, -theta);
            cs.push_back(b[0]);
            cs.push_back(b[1]);
        }
    }

    for (int i = 0; i < cs.size(); i++) {
        bool flag = true;
        for (int m = 0; m < n; m++) {
            if (!c[m].in(cs[i])) {
                flag = false;
                break;
            }
        }
        if (flag) return true;
    }
    return false;
}

double baseline(int n, const vector<double>& l, vector<C>& c) {
    double ok = 0, ng = 100000;
    for (int loop = 0; loop < 1000; loop++) {
        double h = (ok + ng) / 2;
        if (check(h, n, l, c)) ok = h;
        else ng = h;
    }
    return ok;
}

vector<double> generateInput(int n) {
    vector<double> l(n);
    for (int i = 0; i < n; i++) {
        l[i] = 100000.0 * (i + 1);
    }
    return l;
}

vector<C> generateCircles(int n) {
    vector<C> c(n);
    for (int i = 0; i < n; i++) {
        c[i] = C(P(i * 1000.0, i * 1000.0), 0);
    }
    return c;
}