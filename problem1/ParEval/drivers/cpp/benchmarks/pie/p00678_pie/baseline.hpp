#pragma once

#include<vector>
#include<cmath>
#include<algorithm>

using namespace std;

double EPS = 1e-10;

double add(double a, double b) {
    if (abs(a + b) < EPS * (abs(a) + abs(b))) return 0;
    return a + b;
}

struct point {
    double x, y;
    point() {}
    point(double x, double y) : x(x), y(y) {}
    point operator + (point p) {
        return point(add(x, p.x), add(y, p.y));
    }
    point operator - (point p) {
        return point(add(x, -p.x), add(y, -p.y));
    }
    point operator * (double d) {
        return point(x * d, y * d);
    }
    point operator / (double d) {
        return point(x / d, y / d);
    }
};

double dist(point a, point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double baseline(int n, vector<point>& P, vector<double>& V) {
    double r = 0.999;
    point now(0, 0);

    for (double d = 10; d > EPS; d *= r) {
        int mx = 0;
        double mxd = 0;

        for (int j = 0; j < P.size(); j++) {
            if (dist(now, P[j]) / V[j] > mxd) mx = j, mxd = dist(now, P[j]) / V[j];
        }

        now = now + ((P[mx] - now) / dist(P[mx], now) * d);
    }

    double ans = 0;
    for (int i = 0; i < P.size(); i++) {
        ans = max(ans, dist(now, P[i]) / V[i]);
    }
    return ans;
}

vector<point> generatePoints(int n) {
    vector<point> P(n);
    for (int i = 0; i < n; i++) {
        P[i] = point(rand() % 10000, rand() % 10000);
    }
    return P;
}

vector<double> generateVelocities(int n) {
    vector<double> V(n);
    for (int i = 0; i < n; i++) {
        V[i] = 1.0 + (rand() % 1000) / 1000.0;
    }
    return V;
}