#pragma once

#include <vector>
#include <cmath>

using namespace std;

vector<int> baseline(long long N) {
    vector<int> ans;
    int maxn = 1;
    while (maxn * (maxn + 1) / 2 < N) maxn++;
    for (int i = 1; i <= maxn; ++i) {
        if (i != (maxn + 1) * maxn / 2 - N) ans.push_back(i);
    }
    return ans;
}

vector<int> generateInput() {
    return {1000000000000000000LL};
}