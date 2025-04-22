#pragma once

#include <vector>

using namespace std;

typedef vector<int> V;

bool combination(V &a, int t, int i, int c) {
    if (c > t) {
        return false;
    }
    if (c == t) {
        return true;
    }
    if (a.size() == i) {
        return false;
    }
    return combination(a, t, i + 1, c + a[i])
           || combination(a, t, i + 1, c);
}

bool hasCombination(V &a, int t) {
    return combination(a, t, 0, 0);
}

vector<bool> baseline(V &a, int q, vector<int> &queries) {
    vector<bool> results;
    for (int i = 0; i < q; i++) {
        int m = queries[i];
        results.push_back(hasCombination(a, m));
    }
    return results;
}

V generateInput(int n) {
    V a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}