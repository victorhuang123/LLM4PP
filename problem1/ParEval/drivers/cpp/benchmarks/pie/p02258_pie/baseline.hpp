#pragma once

#include <vector>
#include <algorithm>

using namespace std;

long int baseline(const vector<long int>& arr) {
    long int arrmin = arr[0];
    long int dmax = arr[1] - arr[0];

    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] <= arr[i]) {
            dmax = max(arr[i] - arrmin, dmax);
        } else {
            arrmin = min(arr[i], arrmin);
        }
    }
    return dmax;
}

vector<long int> generateInput(int n) {
    vector<long int> arr(n);
    for (int i = 0; i < n; ++i) {
        arr[i] = i + 1;
    }
    return arr;
}