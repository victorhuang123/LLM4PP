#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, const vector<int>& a) {
    vector<vector<int>> oc(n + 1);
    for (int i = 0; i < n; ++i) {
        oc[a[i]].push_back(i + 1);
    }
    int pr = 0, taken = 0;
    for (int i = 1; i <= n; ++i) {
        bool found = false;
        for (auto indx : oc[i]) {
            if (indx > pr) {
                pr = indx;
                taken++;
                found = true;
                break;
            }
        }
        if (!found)
            break;
    }
    if (taken == 0) {
        return -1;
    } else {
        return n - taken;
    }
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        a[i] = i + 1;
    }
    random_shuffle(a.begin(), a.end());
    return a;
}