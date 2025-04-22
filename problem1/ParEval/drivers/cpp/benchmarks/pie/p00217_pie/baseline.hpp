#pragma once

#include <vector>

using namespace std;

typedef struct P {
    int p, d;
    bool operator<(const P &r) {
        return d < r.d;
    }
} P;

P baseline(int n, vector<P>& v) {
    P m = v[0];
    for (int i = 1; i < v.size(); i++) {
        if (m < v[i]) {
            m = v[i];
        }
    }
    return m;
}

vector<P> generateInput(int n) {
    vector<P> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = {i + 1, n - i};
    }
    return v;
}