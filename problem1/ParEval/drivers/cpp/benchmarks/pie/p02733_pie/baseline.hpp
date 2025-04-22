#pragma once

#include <vector>
#include <algorithm>
using namespace std;

int baseline(int h, int w, int k, const vector<vector<int>>& a) {
    vector<vector<int>> pre(h + 1, vector<int>(w + 1, 0));
    int ans = 1e9;
    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            pre[i][j] = a[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
        }
    }
    int top = (1 << (h - 1)) - 1;
    for (int i = top; i >= 0; --i) {
        vector<int> vec = {0};
        int cnt = 1, tmp = 0, pre_col = 0;
        int mask = i;
        while (mask) {
            if (mask & 1) {
                ++tmp;
                vec.push_back(cnt);
            }
            mask >>= 1;
            ++cnt;
        }
        vec.push_back(h);
        for (int col = 1; col <= w; ++col) {
            bool f = false;
            for (size_t j = 1; j < vec.size(); ++j) {
                if (pre[vec[j]][col] - pre[vec[j - 1]][col] - pre[vec[j]][pre_col] + pre[vec[j - 1]][pre_col] > k) {
                    if (pre[vec[j]][col] - pre[vec[j - 1]][col] - pre[vec[j]][col - 1] + pre[vec[j - 1]][col - 1] > k) {
                        f = true;
                        break;
                    }
                }
            }
            if (f) {
                ++tmp;
                pre_col = col - 1;
            }
        }
        ans = min(ans, tmp);
    }
    return ans;
}

vector<vector<int>> generateInput(int h, int w) {
    vector<vector<int>> a(h + 1, vector<int>(w + 1, 1));
    return a;
}