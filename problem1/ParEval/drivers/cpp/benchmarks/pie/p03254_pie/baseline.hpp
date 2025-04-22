#pragma once

#include <vector>
#include <algorithm>

int baseline(int n, int x, std::vector<int>& arr) {
    std::sort(arr.begin(), arr.end()); // Sort array

    int count = 0;
    for(int i = 0; i < n; i++){
        if(x >= arr[i]){
            if(i == n - 1 && (x - arr[i]) != 0){
                return count;
            }
            else{
                count++;
                x = x - arr[i]; // Update x value
            }
        }
    }
    return count;
}

std::vector<int> generateInput(int n) {
    std::vector<int> arr(n, 1); // Array of size n filled with 1s
    return arr;
}