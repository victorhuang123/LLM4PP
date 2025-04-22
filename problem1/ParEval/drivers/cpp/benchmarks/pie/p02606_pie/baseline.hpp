#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int baseline(int l, int r, int d) {
    int ans = 0;
    for (int i = l; i <= r; i++) {
        if (i % d == 0) ans++;
    }
    return ans;
}

vector<int> generateInput() {
    return {1, 1000000000, 2};
}