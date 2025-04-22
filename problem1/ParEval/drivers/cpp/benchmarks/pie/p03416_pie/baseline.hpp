#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int a, int b) {
    vector<int> arr(1000000, 0);
    for (int i = 10000; i < 100000; i++) {
        int num = i;
        int reversed = 0;
        int temp = num;
        while (temp != 0) {
            reversed = reversed * 10 + temp % 10;
            temp /= 10;
        }
        if (num == reversed) {
            arr[i] = arr[i - 1] + 1;
        } else {
            arr[i] = arr[i - 1];
        }
    }
    return arr[b] - arr[a - 1];
}

vector<int> generateInput() {
    return {10000, 99999};
}