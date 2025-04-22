#pragma once

#include <vector>

using namespace std;

int baseline(int n, vector<vector<int>>& b, vector<vector<int>>& f, vector<bool>& v) {
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (!v[i]) {
            v[i] = true;
            int now = b[0][i];
            int maxi = f[0][i];
            int num = 1;
            while (true) {
                v[now] = true;
                bool found = false;
                for (int j = 0; j < 2; j++) {
                    if (!v[b[j][now]]) {
                        if (maxi == f[j][now]) num++;
                        else if (maxi < f[j][now]) {
                            maxi = f[j][now];
                            num = 1;
                        }
                        now = b[j][now];
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    if (maxi == f[1][i]) num++;
                    else if (maxi < f[1][i]) num = 1;
                    break;
                }
                if (now == i) break;
            }
            ans = (ans * num) % 10007;
        }
    }
    return ans;
}

vector<vector<int>> generateInput(int n) {
    vector<vector<int>> b(2, vector<int>(n));
    vector<vector<int>> f(2, vector<int>(n));
    for (int i = 0; i < n; i++) {
        b[0][i] = (i + 1) % n;
        b[1][i] = (i + 2) % n;
        f[0][i] = i;
        f[1][i] = (i + 1) % n;
    }
    return {b, f};
}