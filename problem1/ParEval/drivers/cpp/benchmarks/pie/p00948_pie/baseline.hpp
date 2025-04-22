#pragma once

#include<vector>
#include<algorithm>

struct robot {
    int x, y;
};

int cmp(struct robot a, struct robot b) {
    return a.x < b.x;
}

std::vector<int> baseline(int n, int m, std::vector<robot>& r) {
    std::vector<int> left1(n + 2);
    std::vector<int> right1(n + 2);
    std::vector<int> res(n + 2);

    for (int i = 0; i <= n; i++) {
        left1[i] = right1[i] = i;
    }

    std::sort(r.begin() + 1, r.begin() + m + 1, cmp);

    for (int i = 1; i <= m; i++) {
        int xx = r[i].y;
        left1[xx] = left1[xx + 1] = std::min(left1[xx], left1[xx + 1]);
        right1[xx] = right1[xx + 1] = std::max(right1[xx], right1[xx + 1]);
    }

    std::vector<int> result(n);
    for (int i = 1; i <= n; i++) {
        result[i - 1] = right1[i] - left1[i] + 1;
    }

    return result;
}

std::vector<robot> generateInput(int n, int m) {
    std::vector<robot> r(m + 1);
    for (int i = 1; i <= m; i++) {
        r[i].x = rand() % n + 1;
        r[i].y = rand() % n + 1;
    }
    return r;
}