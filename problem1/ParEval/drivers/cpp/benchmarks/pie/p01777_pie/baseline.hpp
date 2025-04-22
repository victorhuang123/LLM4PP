#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int D, int Q, vector<int>& x, vector<vector<int>>& seg, vector<vector<int>>& queries) {
    for (int i = 0; i < D; i++) {
        int t = i + 131072;
        while (t > 0) {
            seg[t].push_back(x[i]);
            t >>= 1;
        }
    }

    for (int i = 1; i < 262144; i++) {
        if (seg[i].size() > 1) {
            sort(seg[i].begin(), seg[i].end());
        }
    }

    int result = 0;
    for (int i = 0; i < Q; i++) {
        int ls = queries[i][0];
        int rs = queries[i][1];
        int es = queries[i][2];
        int a = min(x[ls - 1], x[rs - 1]);
        int b = max(x[ls - 1], x[rs - 1]);
        int count = 0;
        for (int j = ls - 1; j < rs; j++) {
            if (x[j] < a - es || x[j] > b + es) {
                count++;
            }
        }
        result += rs - ls + 1 - count;
    }
    return result;
}

vector<int> generateInput(int D) {
    vector<int> x(D);
    for (int i = 0; i < D; i++) {
        x[i] = rand() % 1000000;
    }
    return x;
}