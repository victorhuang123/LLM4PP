#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, vector<int>& a) {
    vector<int> g;
    g.push_back(1);
    int c = 0;
    while(true) {
        g.push_back(g[c] * 3 + 1);
        if(g[++c] >= n) break;
    }

    int ret = 0;
    for(int i = c - 1; i >= 0; i--) {
        for(int j = g[i]; j < n; j++) {
            int v = a[j], w = j - g[i];
            while(w >= 0 && a[w] > v) {
                a[w + g[i]] = a[w];
                w -= g[i];
                ret++;
            }
            a[w + g[i]] = v;
        }
    }

    return ret;
}

