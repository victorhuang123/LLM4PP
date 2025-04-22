#pragma once

#include <bits/stdc++.h>

using namespace std;

const int N = 1000 * 1000 + 10, mod = 1e9 + 7;

long long baseline(int n, int m, const vector<int>& row_inputs, const vector<int>& col_inputs) {
    int r[N], c[N];
    long long ans = 1, sr = 0, sc = 0, cnt = 0;

    memset(r, -1, sizeof(r));
    memset(c, -1, sizeof(c));

    for (int i = 0; i < n; i++) {
        int x = row_inputs[i] - 1;
        if (r[x] != -1) {
            return 0;
        }
        r[x] = i;
    }

    for (int i = 0; i < m; i++) {
        int x = col_inputs[i] - 1;
        if (c[x] != -1) {
            return 0;
        }
        c[x] = i;
    }

    for (int i = n * m - 1; i >= 0; i--) {
        if (r[i] >= 0 && c[i] >= 0) {
            cnt++, sr++, sc++;
            continue;
        }

        if (r[i] == -1 && c[i] == -1) {
            if (sr * sc - cnt <= 0) {
                return 0;
            }
            ans = (ans * (sr * sc - cnt)) % mod;
            cnt++;
            continue;
        }

        if (r[i] == -1) {
            if (!sc) {
                return 0;
            }
            ans = ans * sc % mod;
            cnt++, sr++;
            continue;
        }

        if (c[i] == -1) {
            if (!sr) {
                return 0;
            }
            ans = ans * sr % mod;
            cnt++, sc++;
            continue;
        }
    }

    return ans;
}

vector<int> generateInput(int size) {
    vector<int> input(size);
    for (int i = 0; i < size; i++) {
        input[i] = i + 1;
    }
    return input;
}