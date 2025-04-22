#pragma once

#include <vector>
#include <climits>

using namespace std;

long long baseline(int n, const vector<int>& arr) {
    long long ans = LONG_LONG_MAX;
    for(int i = 0; i <= 1e4; i++) {
        long long sum = 0;
        for(int j = 0; j < n; j++) {
            sum += (long long)(arr[j] - i) * (arr[j] - i);
        }
        if(sum < ans) {
            ans = sum;
        }
    }
    return ans;
}

vector<int> generateInput() {
    int n = 1e5;
    vector<int> arr(n);
    for(int i = 0; i < n; i++) {
        arr[i] = i % 10000;
    }
    return arr;
}