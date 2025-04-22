#pragma once

#include <vector>
#include <string>

using namespace std;

vector<pair<int, int>> baseline(int H, int W, int R, int C, const vector<string>& s, const vector<string>& t) {
    vector<unsigned long long> power(1001);
    vector<vector<unsigned long long>> h1(H, vector<unsigned long long>(W - C + 1));
    vector<unsigned long long> h2(R);

    power[0] = 1;
    for (int i = 1; i <= 1000; i++) power[i] = power[i - 1] * 257;

    for (int i = 0; i < H; i++) {
        unsigned long long val = 0;
        for (int j = 0; j < C; j++) val = val * 257 + s[i][j];
        h1[i][0] = val;
        for (int j = C; j < W; j++) val = val * 257 + s[i][j] - power[C] * s[i][j - C], h1[i][j - C + 1] = val;
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) h2[i] = h2[i] * 257 + t[i][j];
    }

    vector<pair<int, int>> result;
    for (int i = 0; i <= H - R; i++) {
        for (int j = 0; j <= W - C; j++) {
            bool flag = true;
            for (int k = i; k < i + R; k++) {
                if (h1[k][j] != h2[k - i]) {
                    flag = false; break;
                }
            }
            if (flag) {
                result.emplace_back(i, j);
            }
        }
    }

    return result;
}

vector<string> generateInput(int H, int W, int R, int C) {
    vector<string> s(H, string(W, 'a'));
    vector<string> t(R, string(C, 'a'));
    return s;
}