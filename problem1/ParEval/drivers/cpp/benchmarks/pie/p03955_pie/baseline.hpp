#pragma once

#include<bits/stdc++.h>
using namespace std;

vector<int> generateInput(int n) {
    vector<int> input(3 * n);
    for (int i = 0; i < 3 * n; ++i) {
        input[i] = rand() % 1000000 + 1;
    }
    return input;
}

bool baseline(int n, const vector<int>& a, const vector<int>& fu, const vector<bool>& vis) {
    vector<int> c(n + 1, 0);
    int s1 = 0, s2 = 0;

    for (int i = 1; i <= 3; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x = a[(i - 1) * n + (j - 1)];
            if (i == 1) {
                if (x % 3 == 0) {
                    if (j & 1) s1++;
                    else s2++;
                } else {
                    if (x % 3 != 1) return false;
                }
                if (vis[j]) return false;
                if ((j & 1) ^ (x & 1)) return false;
            } else {
                if (fu[j]) {
                    if (x != a[j] * 3 - i + 1) return false;
                } else {
                    if (x != (a[j] - 1) * 3 + i) return false;
                }
            }
        }
    }

    int i = (n & 1) ? n : n - 1;
    for (; i > 0; i -= 2) {
        s2 += c[a[i]];
        c[a[i]]++;
    }

    fill(c.begin(), c.end(), 0);
    i = (n & 1) ? n - 1 : n;
    for (; i > 0; i -= 2) {
        s1 += c[a[i]];
        c[a[i]]++;
    }

    return (s1 % 2 == 0 && s2 % 2 == 0);
}