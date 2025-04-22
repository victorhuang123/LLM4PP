#pragma once

#include<vector>
#include<iostream>
#include<algorithm>

std::vector<std::string> baseline(long int n, long int k, const std::vector<long int>& a) {
    std::vector<std::string> result;
    for(long int i = k; i < n; i++) {
        if(a[i] > a[i - k]) result.push_back("Yes");
        else result.push_back("No");
    }
    return result;
}

std::vector<long int> generateInput(long int n) {
    std::vector<long int> a(n);
    for(long int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}