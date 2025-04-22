#pragma once

#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

pair<int, int> baseline(int a, vector<int>& arr) {
    int max = 0;
    for (int i = 1; i < a; i++) {
        if (arr[i] > arr[max]) max = i;
    }

    int ans2 = -1;
    int temp = arr[max] / 2;

    for (int i = 0; i < a; i++) {
        if (i == max) continue;
        else if (ans2 == -1) ans2 = i;
        else {
            int t1 = abs(temp - arr[ans2]), t2 = abs(temp - arr[i]);
            if (t2 < t1) ans2 = i;
        }
    }

    return make_pair(arr[max], arr[ans2]);
}

vector<int> generateInput(int size) {
    vector<int> arr(size);
    for (int i = 0; i < size; i++) {
        arr[i] = i + 1;
    }
    return arr;
}