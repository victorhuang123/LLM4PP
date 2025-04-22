#pragma once

#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

struct Node {
    double x, y;
};

struct Line {
    Node l, r;
    bool operator<(const Line& b) const {
        return l.y < b.l.y || (l.y == b.l.y && r.y < b.r.y);
    }
};

inline double xmulti(const Node& a, const Line& b) {
    return (b.l.x - a.x) * (b.r.y - a.y) - (b.l.y - a.y) * (b.r.x - a.x);
}

int baseline(int n, int m, int w, int h, int s, const vector<Node>& nodes, const vector<pair<double, double>>& lines) {
    vector<Line> a(m + 2);
    a[0].l.y = a[0].r.y = 0;
    a[0].l.x = 0; a[0].r.x = w;
    for (int i = 1; i <= m; i++) {
        a[i].l.y = lines[i-1].first;
        a[i].r.y = lines[i-1].second;
        a[i].l.x = 0; a[i].r.x = w;
    }
    a[m+1].l.y = a[m+1].r.y = h;
    a[m+1].l.x = 0; a[m+1].r.x = w;
    sort(a.begin(), a.end());
    vector<double> area(m+1);
    for (int i = 0; i <= m; i++) {
        area[i] = ((a[i+1].l.y - a[i].l.y) + (a[i+1].r.y - a[i].r.y)) * w / 2;
    }
    vector<int> sum(m+2, 0);
    for (const auto& node : nodes) {
        int l = 0, r = m+1;
        int mid;
        while (l <= r) {
            mid = (l + r) / 2;
            if (xmulti(node, a[mid]) > 0) {
                if (xmulti(node, a[mid+1]) < 0)
                    break;
                else
                    l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        sum[mid]++;
    }
    int ans = -1;
    int tot = 0;
    double totarea = 0;
    int i = 0, j = 0;
    for (i = 0; i <= m; i++) {
        j = max(i, j);
        if (totarea > 0) {
            totarea -= area[i-1];
            tot -= sum[i-1];
        }
        while (j <= m && area[j] + totarea <= w * h - s) {
            totarea += area[j];
            tot += sum[j];
            j++;
        }
        ans = max(ans, tot);
    }
    return n - ans;
}

vector<Node> generateNodes(int n) {
    vector<Node> nodes(n);
    for (int i = 0; i < n; i++) {
        nodes[i].x = rand() % 10000;
        nodes[i].y = rand() % 10000;
    }
    return nodes;
}

vector<pair<double, double>> generateLines(int m) {
    vector<pair<double, double>> lines(m);
    for (int i = 0; i < m; i++) {
        lines[i].first = rand() % 10000;
        lines[i].second = rand() % 10000;
    }
    return lines;
}