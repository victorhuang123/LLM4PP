#pragma once

#include<vector>
#include<algorithm>

int baseline(int n, const std::vector<int>& a) {
    std::vector<int> arr = a;
    int sum = 0;
    for(int i = 1; i <= n; i++) {
        if(arr[i] == i) {
            std::swap(arr[i], arr[i+1]);
            sum++;
        }
    }
    return sum;
}

std::vector<int> generateInput(int n) {
    std::vector<int> a(n + 2);
    for(int i = 1; i <= n; i++) {
        a[i] = i;
    }
    return a;
}