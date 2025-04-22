#pragma once

#include<vector>
#include<algorithm>

using namespace std;

bool baseline(int n, const vector<int>& a) {
    int ans = 0;
    int maxx = 0;
    for(int i = 0; i < n; i++) {
        maxx = max(maxx, a[i]);
        ans += a[i];
    }
    return maxx < ans - maxx;
}

vector<int> generateInput() {
    const int M = 200005;
    vector<int> a(M);
    for(int i = 0; i < M; i++) {
        a[i] = i + 1;
    }
    return a;
}