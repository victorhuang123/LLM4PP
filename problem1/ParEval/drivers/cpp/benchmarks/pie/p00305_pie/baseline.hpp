#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, const vector<vector<int>>& y) {
    vector<vector<int>> mp(n, vector<int>(n)), x(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) mp[i][j] = x[i][j] = y[i][j];

    int ans = max(y[0][n - 1], y[n - 1][0]);
    for (int i = 0; i < n; i++)
        for (int j = n - 2; j >= 0; j--) {
            x[i][j] += x[i][j + 1];
            mp[j][i] += mp[j + 1][i];
            if (ans < x[i][j]) ans = x[i][j];
            if (ans < mp[j][i]) ans = mp[j][i];
        }

    vector<vector<int>> sum(n + 1, vector<int>(n + 1, -100000000));
    vector<vector<vector<int>>> K(2, vector<vector<int>>(n, vector<int>(n)));

    int t = 0;
    while (1) {
        t++;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                int a = K[t % 2][i][j];
                K[(t + 1) % 2][i][j] = a;
                sum[i][j] = -100000000;
                for (int k = a + 1; k < n; k++) {
                    int X = (x[a][i] - x[a][j + 1]) + (x[k][i] - x[k][j + 1]);
                    int Y = (mp[a + 1][i] - mp[k][i]) + (mp[a + 1][j] - mp[k][j]);
                    if (sum[i][j] <= X + Y) sum[i][j] = X + Y, K[(t + 1) % 2][i][j] = k;
                    ans = max(ans, sum[i][j]);
                }
            }

        int f = 1;
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++)
                for (int k = K[t % 2][i][j] + 1; k < K[(t + 1) % 2][i][j]; k++) {
                    f = 0;
                    int X = (x[k][i + 1] - x[k][j]) - (x[k - 1][i] - x[k - 1][j + 1]);
                    sum[i][j] += X;
                    ans = max(ans, sum[i][j]);
                }
        if (f) break;
    }
    return ans;
}

vector<vector<int>> generateInput(int n) {
    vector<vector<int>> y(n, vector<int>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            y[i][j] = rand() % 1000000;
    return y;
}