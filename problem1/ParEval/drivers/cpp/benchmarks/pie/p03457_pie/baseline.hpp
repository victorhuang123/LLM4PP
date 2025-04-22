#pragma once

#include <vector>
#include <cstdio>

int baseline(int n) {
    int jin = 0;
    std::vector<int> ti(n + 1, 0);
    std::vector<int> xi(n + 1, 0);
    std::vector<int> yi(n + 1, 0);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d", &ti[i], &xi[i], &yi[i]);
        int sum = xi[i] + yi[i] - xi[i-1] - yi[i-1];
        if (jin != 0) continue;

        if (sum < 0) {
            sum = -sum;
        }

        if (ti[i] >= sum) {
            int l1 = (ti[i] - ti[i-1]) % 2;
            int l2 = sum % 2;
            if (l1 != l2) {
                jin = 1;
            }
        } else {
            jin = 1;
        }
    }

    return jin;
}

std::vector<std::vector<int>> generateInput(int n) {
    std::vector<std::vector<int>> input(n, std::vector<int>(3));
    for (int i = 0; i < n; i++) {
        input[i][0] = i + 1;
        input[i][1] = i;
        input[i][2] = i;
    }
    return input;
}