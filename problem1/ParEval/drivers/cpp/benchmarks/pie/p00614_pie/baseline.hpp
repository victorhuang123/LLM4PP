#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int P, vector<int> N) {
    vector<int> c = {1, 5, 10, 50, 100, 500};
    int end = 0;
    for(int i = 0; i < 6; i++) {
        end += c[i] * N[i];
    }
    int ans = 10000000;
    for(int i = P; i <= end; i++) {
        int cur = 0;
        int t = i - P;
        for(int j = 5; j >= 0; j--) {
            cur += t / c[j];
            t %= c[j];
        }
        int l = i;
        for(int j = 5; j >= 0; j--) {
            int tmp = l / c[j];
            cur += min(N[j], tmp);
            l -= min(N[j], tmp) * c[j];
        }
        if(l != 0) continue;
        ans = min(ans, cur);
    }
    return ans;
}

vector<int> generateInput() {
    return {1000000, 1000000, 1000000, 1000000, 1000000, 1000000};
}