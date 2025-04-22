#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef long long LL;

LL baseline(LL n, vector<string>& numbers) {
    LL cnt[20][20] = {0};
    LL sum[20][20] = {0};
    LL ans = 0;

    for (int i = 0; i < n; ++i) {
        string s = numbers[i];
        bool p = false;
        LL x = 0;
        int two = 0, five = 0;
        for (char c : s) {
            if (c == '.') {
                p = true;
            } else {
                x = (x * 10) + c - '0';
                two -= p;
                five -= p;
            }
        }
        while (x % 2 == 0) {
            ++two;
            x /= 2;
        }
        while (x % 5 == 0) {
            ++five;
            x /= 5;
        }
        two = min(two, 9);
        five = min(five, 9);
        cnt[10 + two][10 + five] += 1;
        sum[10 - two][10 - five] += 1;
    }

    for (int i = 0; i < 20; ++i) {
        for (int j = 1; j < 20; ++j) {
            sum[i][j] += sum[i][j - 1];
        }
    }

    for (int i = 1; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            sum[i][j] += sum[i - 1][j];
        }
    }

    for (int i = -9; i <= 9; ++i) {
        for (int j = -9; j <= 9; ++j) {
            ans += sum[10 + i][10 + j] * cnt[10 + i][10 + j];
            if (i >= 0 && j >= 0) {
                ans -= cnt[10 + i][10 + j];
            }
        }
    }

    return ans / 2;
}

vector<string> generateInput(LL n) {
    vector<string> numbers(n);
    for (LL i = 0; i < n; ++i) {
        numbers[i] = "1234567890.1234567890";
    }
    return numbers;
}