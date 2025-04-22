#pragma once

#include <bits/stdc++.h>

using namespace std;

string baseline(int n, vector<int>& a) {
    vector<int> c(200005, 0);
    int q = 0, m = 233;

    for (int i = 0; i < n; i++) {
        c[a[i]]++;
        q = max(q, a[i]);
        m = min(m, a[i]);
    }

    int flag = 0;
    if (m != (q + 1) / 2) flag = 1;
    else {
        if ((q % 2 == 1 && c[m] != 2) || (q % 2 == 0 && c[m] != 1)) flag = 1;
        else {
            for (int i = m + 1; i <= q; i++) {
                if (c[i] < 2) { flag = 1; break; }
            }
        }
    }

    if (flag) return "Impossible";
    else return "Possible";
}

vector<int> generateInput() {
    vector<int> a;
    for (int i = 1; i <= 100000; i++) {
        a.push_back(i);
        a.push_back(i);
    }
    return a;
}