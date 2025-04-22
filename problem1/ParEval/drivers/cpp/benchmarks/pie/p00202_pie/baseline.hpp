#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int n, int x, vector<int>& data) {
    vector<bool> dp(x + 1, false);
    dp[0] = true;

    for (int i = 0; i < n; i++) {
        for (int j = x; j >= 0; j--) {
            if (dp[j] && j + data[i] <= x) {
                dp[j + data[i]] = true;
            }
        }
    }

    for (int i = x; i >= 2; i--) {
        if (dp[i]) {
            bool isPrime = true;
            for (int j = 2; j * j <= i; j++) {
                if (i % j == 0) {
                    isPrime = false;
                    break;
                }
            }
            if (isPrime) {
                return i;
            }
        }
    }

    return -1;
}

vector<int> generateInput() {
    int n = 1000;
    int x = 1000000;
    vector<int> data(n);
    for (int i = 0; i < n; i++) {
        data[i] = rand() % 1000 + 1;
    }
    return data;
}