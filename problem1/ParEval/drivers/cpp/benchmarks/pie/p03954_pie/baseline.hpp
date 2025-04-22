#pragma once

#include <vector>
#include <cstring>

int baseline(int n, const std::vector<int>& a) {
    n = n * 2 - 1;
    int l = 0, r = 1e9 + 7, ans = 0;
    std::vector<int> b(n + 2);

    while (l <= r) {
        int mid = l + r >> 1;
        for (int i = 1; i <= n; i++) {
            if (a[i] > mid) b[i] = 1;
            else b[i] = 0;
        }
        b[n + 1] = b[n];
        b[0] = b[1];
        int p = 0;
        for (int i = 1; i <= n + 1; i++) {
            if (b[i - 1] != b[i]) p++;
            if (b[i - 1] == b[i] && p) {
                if (p % 2 == 0) {
                    for (int j = i - p; j <= i - 1; j++) b[j] = b[i];
                } else {
                    int q = p >> 1;
                    for (int j = i - p; j <= i - q - 2; j++) b[j] = b[i - p - 1];
                    for (int j = i - q - 1; j <= i - 1; j++) b[j] = b[i];
                }
                p = 0;
            }
        }
        if (b[n / 2 + 1]) {
            l = mid + 1;
        } else {
            r = mid - 1;
            ans = mid;
        }
        std::memset(b.data(), 0, b.size() * sizeof(int));
    }
    return ans;
}

std::vector<int> generateInput(int n) {
    std::vector<int> a(n * 2);
    for (int i = 0; i < n * 2; i++) {
        a[i] = i + 1;
    }
    return a;
}