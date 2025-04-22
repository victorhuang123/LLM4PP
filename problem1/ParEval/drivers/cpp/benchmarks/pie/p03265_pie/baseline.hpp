#pragma once

#include <vector>

struct Result {
    int p3_x, p3_y, p4_x, p4_y;
};

Result baseline(int x1, int y1, int x2, int y2) {
    struct node {
        int x, y;
        int len;

        node() {};
        node(int xx, int yy) { x = xx; y = yy; len = x * x + y * y; }

        bool judge(node t) {
            if (t.len == len && (x * t.y - y * t.x) > 0 && (t.x * x + t.y * y) == 0) return 1;
            else return 0;
        }
    };

    node p1, p2, p3, p4, tt, t;
    p1 = node(x1, y1);
    p2 = node(x2, y2);
    tt = node(p2.x - p1.x, p2.y - p1.y);

    for (int i = -400; i <= 400; ++i) {
        for (int j = -400; j <= 400; ++j) {
            t = node(i, j);
            t = node(t.x - p2.x, t.y - p2.y);
            if (tt.judge(t)) p3 = node(i, j);
            t = node(i, j);
            t = node(p1.x - t.x, p1.y - t.y);
            if (t.judge(tt)) p4 = node(i, j);
        }
    }
    return {p3.x, p3.y, p4.x, p4.y};
}