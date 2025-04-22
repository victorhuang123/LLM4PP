#pragma once

#include<vector>
#include<algorithm>

using namespace std;

vector<int> baseline(int a, int b, int c, int n, vector<int>& x, vector<int>& y, vector<int>& z, vector<bool>& r) {
    vector<int> f(300, 2);
    int m = a + b + c;

    int cnt = 0;
    while (cnt < 100000) {
        for (int i = 0; i < n; i++) {
            int a_idx = x[i], b_idx = y[i], c_idx = z[i];
            bool Flag = r[i];
            if (Flag) {
                f[a_idx] = f[b_idx] = f[c_idx] = 1;
            } else {
                if (f[b_idx] == 1 && f[c_idx] == 1) {
                    f[a_idx] = 0;
                }
                if (f[a_idx] == 1 && f[c_idx] == 1) {
                    f[b_idx] = 0;
                }
                if (f[a_idx] == 1 && f[b_idx] == 1) {
                    f[c_idx] = 0;
                }
            }
        }
        cnt++;
    }

    return vector<int>(f.begin(), f.begin() + m);
}

vector<int> generate_input(int a, int b, int c, int n) {
    vector<int> x(n), y(n), z(n);
    vector<bool> r(n);
    for (int i = 0; i < n; i++) {
        x[i] = rand() % 300;
        y[i] = rand() % 300;
        z[i] = rand() % 300;
        r[i] = rand() % 2;
    }
    return {x, y, z, r};
}