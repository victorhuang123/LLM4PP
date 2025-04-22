#pragma once

#include <bits/stdc++.h>
using namespace std;

int baseline(int n, int k, const vector<int>& nums) {
    unordered_map<int, int> freqMap;
    for (int num : nums) {
        freqMap[num]++;
    }

    vector<int> frequencies;
    for (auto& pair : freqMap) {
        frequencies.push_back(pair.second);
    }

    sort(frequencies.begin(), frequencies.end());
    int res = 0;
    for (int i = 0; i < frequencies.size() - k; i++) {
        res += frequencies[i];
    }

    return res;
}

vector<int> generateInput(int n) {
    return vector<int>(n, 1); // A large array with n elements, all set to 1.
}