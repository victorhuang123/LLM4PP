#pragma once

#include<vector>
#include<algorithm>

using namespace std;

struct block {
    int x1, x2, y, f;
};

bool comp(const block &b1, const block &b2) {
    return b1.y < b2.y;
}

int baseline(int n, int r, const vector<block>& blocks) {
    vector<vector<int>> fie(10002, vector<int>(2, 0));
    vector<block> b = blocks;

    sort(b.begin(), b.end(), comp);

    int ny = 0;
    int now = 0, prev = 1;
    int res = 0, res2 = 0;

    for (int i = 0; i < n * 2; i++) {
        if (ny != b[i].y) {
            swap(now, prev);
            int cnt = 0;
            int cnt2 = 0, bt = 0, cnt3 = 0;
            for (int j = 0; j <= 10000; j++) {
                if (fie[j][now] > 0 && fie[j][prev] == 0) cnt3++;
                if (fie[j][now] == 0 && fie[j][prev] > 0) cnt3++;
                fie[j][now] = fie[j][prev];
                if (fie[j][now] > 0) {
                    cnt++;
                    if (bt == 0) cnt2++, bt = 1;
                } else bt = 0;
            }
            res += cnt * (b[i].y - ny);
            res2 += cnt2 * 2 * (b[i].y - ny) + cnt3;
        }
        ny = b[i].y;
        for (int j = b[i].x1; j <= b[i].x2; j++) fie[j][now] += b[i].f;
    }

    if (r == 2) {
        swap(now, prev);
        int cnt3 = 0;
        for (int j = 0; j <= 10000; j++) {
            if (fie[j][now] > 0 && fie[j][prev] == 0) cnt3++;
            if (fie[j][now] == 0 && fie[j][prev] > 0) cnt3++;
            fie[j][now] = fie[j][prev];
        }
        res2 += cnt3;
        return res2;
    }

    return res;
}

vector<block> generateInput(int n) {
    vector<block> blocks(n * 2);
    for (int i = 0; i < n; i++) {
        int y1 = i * 2, y2 = y1 + 1;
        blocks[i * 2] = {i, i + 1, y1, 1};
        blocks[i * 2 + 1] = {i, i + 1, y2, -1};
    }
    return blocks;
}