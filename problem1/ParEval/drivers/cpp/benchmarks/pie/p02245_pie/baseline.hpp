#pragma once

#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

int baseline(const vector<int>& s) {
    vector<int> gg = {1, 2, 3, 4, 5, 6, 7, 8, 0};
    vector<vector<int>> ff = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    struct node {
        vector<int> a;
        int step;
    };

    map<int, int> m;
    int sum = 1;
    node tt;
    tt.a = s;
    tt.step = 0;
    queue<node> q;
    q.push(tt);

    while (!q.empty()) {
        node star = q.front();
        q.pop();
        int i;
        for (i = 0; i < 9; i++)
            if (star.a[i] == 0)
                break;
        int y = i / 3;
        int x = i % 3;

        for (i = 0; i < 4; i++) {
            int tx = x + ff[i][0];
            int ty = y + ff[i][1];
            if (tx >= 0 && ty >= 0 && ty < 3 && tx < 3) {
                node end;
                end.a = star.a;
                int k = ty * 3 + tx;
                swap(end.a[k], end.a[y * 3 + x]);
                int sum1 = 0;
                for (int j = 0; j < 9; j++)
                    sum1 = sum1 * 10 + end.a[j];
                if (!m[sum1]) {
                    m[sum1] = sum++;
                    end.step = star.step + 1;
                    if (end.a == gg)
                        return end.step;
                    q.push(end);
                }
            }
        }
    }
    return -1;
}

vector<int> generateInput() {
    return {8, 1, 3, 4, 0, 2, 7, 6, 5};
}