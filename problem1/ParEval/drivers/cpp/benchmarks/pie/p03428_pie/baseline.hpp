#pragma once

#include <vector>
#include <map>
#include <cmath>
#include <utility>

using namespace std;

typedef pair<double, double> pdd;
typedef pair<int, int> pii;

struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

struct Vector {
    double x, y;
    Vector(double x = 0, double y = 0) : x(x), y(y) {}
    Vector operator-(const Vector& other) const {
        return Vector(x - other.x, y - other.y);
    }
};

Vector rotate(const Vector& v, double angle) {
    double c = cos(angle), s = sin(angle);
    return Vector(v.x * c - v.y * s, v.x * s + v.y * c);
}

double arg(const Vector& v) {
    return atan2(v.y, v.x);
}

vector<double> baseline(int N, vector<pdd>& points) {
    vector<Point> g;
    map<pdd, int> M;
    for (int i = 0; i < N; i++) {
        double x = points[i].first, y = points[i].second;
        g.emplace_back(Point(x, y));
        M[pdd(x, y)] = i;
    }

    vector<Point> s = g; // Placeholder for ConvexHull
    vector<double> ans(N, 0.0);
    int sz = s.size();
    for (int i = 0; i < sz; i++) {
        int now = M[pdd(s[i].x, s[i].y)];
        Vector a = Vector(s[i].x, s[i].y) - Vector(s[(i + sz - 1) % sz].x, s[(i + sz - 1) % sz].y);
        Vector b = Vector(s[(i + 1) % sz].x, s[(i + 1) % sz].y) - Vector(s[i].x, s[i].y);
        a = rotate(a, -M_PI * 0.5); b = rotate(b, -M_PI * 0.5);
        double bb = arg(b), aa = arg(a);
        if (bb * aa < 0 && aa > 0) {
            bb = 2 * M_PI + bb;
        }
        double d = bb - aa;
        ans[now] = abs(d / (2 * M_PI));
    }
    return ans;
}

vector<pdd> generateInput(int N) {
    vector<pdd> points;
    for (int i = 0; i < N; i++) {
        double x = static_cast<double>(rand()) / RAND_MAX * 1000;
        double y = static_cast<double>(rand()) / RAND_MAX * 1000;
        points.emplace_back(x, y);
    }
    return points;
}