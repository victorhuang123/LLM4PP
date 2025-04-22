#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int n, int k, const vector<int>& arr) {
    int y = 0;
    for (int i = 0; i < n; i++) {
        int x = arr[i];
        if (x > k) {
            y += (x - k) * 2;
        }
        else if (k - x < x) {
            y += (k - x) * 2;
        }
        else {
            y += x * 2;
        }
    }
    return y;
}

vector<int> generateInput(int n) {
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1; // Example input: 1, 2, 3, ..., n
    }
    return arr;
}