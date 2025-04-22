#pragma once

#include <vector>
#include <algorithm>

void dfs(int a, int b, int c, int num, int fl, std::vector<int>& sum) {
    if (num > 1e9) {
        return;
    }
    if (fl > 9)
        return;
    if (a && b && c) {
        sum.push_back(num);
        dfs(1, b, c, num * 10 + 3, fl + 1, sum);
        dfs(a, 1, c, num * 10 + 5, fl + 1, sum);
        dfs(a, b, 1, num * 10 + 7, fl + 1, sum);
    } else {
        dfs(1, b, c, num * 10 + 3, fl + 1, sum);
        dfs(a, 1, c, num * 10 + 5, fl + 1, sum);
        dfs(a, b, 1, num * 10 + 7, fl + 1, sum);
    }
}

int baseline(int key) {
    std::vector<int> sum;
    dfs(0, 0, 0, 0, 0, sum);
    std::sort(sum.begin(), sum.end());

    int left = 0;
    int right = sum.size() - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (sum[mid] > key) {
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return right + 1;
}

std::vector<int> generateInput() {
    return {1000000000};
}