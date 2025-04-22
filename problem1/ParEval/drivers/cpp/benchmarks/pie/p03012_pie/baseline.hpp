#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int baseline(int n, const vector<int>& v) {
    int s1 = 0, s2 = 0, ans = INT_MAX, temp = 0;

    for (int i = 0; i < n; i++) {
        temp += v[i];
        int aux = 0;
        for (int j = i + 1; j < n; j++) {
            aux += v[j];
        }
        ans = min(ans, abs(aux - temp));
    }

    return ans;
}

vector<int> generateInput() {
    int n = 10000;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
        v[i] = i + 1;
    }
    return v;
}