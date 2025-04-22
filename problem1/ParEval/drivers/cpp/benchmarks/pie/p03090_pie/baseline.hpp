#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int n) {
    vector<vector<int>> brr(n + 1, vector<int>(n + 1, 0));
    int sum = 0;
    int pp = 0;

    if (n % 2) {
        pp = n - 1;
    } else {
        pp = n;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (j != pp && (brr[i][j] == 0 && brr[j][i] == 0) && i != j) {
                brr[i][j] = 1;
                sum++;
            }
        }
        pp--;
    }

    return sum;
}

vector<int> generateInput() {
    return {1000};  // Example input to maximize problem scale
}