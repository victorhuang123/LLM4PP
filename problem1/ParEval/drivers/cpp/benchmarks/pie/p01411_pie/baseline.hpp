#pragma once

#include <vector>
#include <algorithm>

using namespace std;

double baseline(int h, int n, int p, int m, int k, vector<pair<int, int>>& edges) {
    vector<int> v(h, -1);
    for (int i = 0; i < m; ++i) {
        int a = edges[i].first;
        int b = edges[i].second;
        v[a - 1] = b - 1;
    }

    double cmb[512][512] = {};
    for (int i = 0; i < 512; ++i) {
        cmb[i][0] = 1;
        for (int j = 1; j <= i; ++j) {
            cmb[i][j] = cmb[i - 1][j - 1] + cmb[i - 1][j];
        }
    }

    int rst = h - m;
    vector<vector<double>> dp1(k + 1, vector<double>(n)), dp2;
    dp2 = dp1;
    dp1[k][p - 1] = 1;

    for (int g = h - 1; g >= 0; --g) {
        if (v[g] == -1) {
            dp2[0] = dp1[0];
            for (int i = 1; i <= k; ++i) {
                double pr1 = 1 - cmb[rst - 1][i] / cmb[rst][i];
                double pr2 = pr1 / (n - 1);
                for (int j = 0; j < n; ++j) {
                    dp2[i][j] = dp1[i][j] * (1 - pr1);
                }
                dp2[i - 1][0] += (dp1[i][0] * (n - 2) + dp1[i][1]) * pr2;
                dp2[i - 1][n - 1] += (dp1[i][n - 1] * (n - 2) + dp1[i][n - 2]) * pr2;
                for (int j = 1; j < n - 1; ++j) {
                    dp2[i - 1][j] += (dp1[i][j] * (n - 3) + dp1[i][j - 1] + dp1[i][j + 1]) * pr2;
                }
            }
            dp1.swap(dp2);
            --rst;
        } else {
            for (int i = 0; i <= k; ++i) {
                swap(dp1[i][v[g]], dp1[i][v[g] + 1]);
            }
        }
    }

    return *max_element(dp1[0].begin(), dp1[0].end());
}

vector<pair<int, int>> generateInput(int h, int m) {
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; ++i) {
        edges[i] = {i + 1, (i + 2) % h + 1};
    }
    return edges;
}