#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int x, int y, int z, vector<int>& v, vector<int>& e, vector<int>& a) {
    vector<vector<double>> pb(y + 1, vector<double>(5001, 0.0));
    pb[0][0] = 1.0;

    for (int i = 0; i < y; ++i) {
        for (int j = 0; j <= 5000; ++j) {
            if (pb[i][j] == 0.0) continue;
            for (int k = 0; k < x; ++k) {
                int next = min(y, i + v[k]);
                int value = j;
                if (e[next] == 1) next = min(y, next + a[next]);
                else if (e[next] == 2) value = j + a[next];
                else if (e[next] == 3) value = max(0, j - a[next]);
                pb[next][value] += pb[i][j] / x;
            }
        }
    }

    double ans = 0.0;
    for (int i = 0; i <= 5000; ++i) {
        ans += pb[y][i] * i;
    }
    return static_cast<int>(ans);
}

vector<int> generateInput(int x, int y, int z) {
    vector<int> v(x, 1);
    vector<int> e(y + 1, 0);
    vector<int> a(y + 1, 0);

    for (int i = 0; i < x; ++i) v[i] = rand() % 10 + 1;
    for (int i = 0; i <= y; ++i) e[i] = rand() % 4;
    for (int i = 0; i <= y; ++i) a[i] = rand() % 100;

    return v, e, a;
}