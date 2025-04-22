#pragma once

#include <vector>

using namespace std;

long long baseline(int r, int c, int q, vector<int>& a, vector<int>& b, vector<int>& o) {
    vector<bool> row(r, false);
    vector<bool> col(c, false);
    long long ans = 0;
    int nr = 0, nc = 0;

    for (int i = q - 1; i >= 0; i--) {
        if (a[i]) {
            if (!col[b[i]]) {
                if (o[i]) ans += r - nr;
                col[b[i]] = true;
                nc++;
            }
        } else {
            if (!row[b[i]]) {
                if (o[i]) ans += c - nc;
                row[b[i]] = true;
                nr++;
            }
        }
    }

    return ans;
}

vector<int> generateInput(int r, int c, int q) {
    vector<int> a(q, 1);
    vector<int> b(q);
    vector<int> o(q, 1);

    for (int i = 0; i < q; i++) {
        b[i] = i % c;
    }

    return {a, b, o};
}