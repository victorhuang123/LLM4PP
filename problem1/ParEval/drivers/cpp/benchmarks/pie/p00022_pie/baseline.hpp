#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int n, const vector<int>& a) {
    int tmp;
    int ans;

    ans = a[0];
    for(int i=0;i<n;i++){
        tmp = 0;
        for(int j=i;j<n;j++){
            tmp += a[j];
            ans = max(tmp,ans);
        }
    }

    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}