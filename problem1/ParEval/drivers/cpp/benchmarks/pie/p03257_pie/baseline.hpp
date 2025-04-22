#pragma once

#include <vector>
#include <algorithm>

long long gcd(long long a, long long b) { return b == 0 ? a : gcd(b, a % b); }

std::vector<std::vector<long long>> baseline(int n) {
    if (n == 2) {
        return {{4, 7}, {23, 10}};
    }

    std::vector<bool> is(100001, false);
    std::vector<int> pri;
    for (int i = 2; i <= 100000; i++) {
        if (!is[i]) pri.push_back(i);
        for (int j = 0; j < pri.size() && i * pri[j] <= 100000; j++) {
            is[i * pri[j]] = true;
            if (i % pri[j] == 0) break;
        }
    }

    std::vector<std::vector<long long>> m(n + 1, std::vector<long long>(n + 1, 0));
    int j = 1;

    for (int i = 2; i <= 2 * n; i += 2) {
        for (int k = 0; k <= n; k++) {
            if (k + 1 >= 1 && k + 1 <= n && i - k >= 1 && i - k <= n) m[k + 1][i - k] = pri[j];
        }
        j++;
    }

    for (int i = (n / 2 * 2); i >= -n; i -= 2) {
        for (int k = 0; k <= n; k++) {
            if (k + 1 >= 1 && k + 1 <= n && i + k >= 1 && i + k <= n) m[k + 1][i + k] *= pri[j];
        }
        j++;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (!m[i][j]) {
                m[i][j] = 1;
                if (i != 1) m[i][j] = m[i][j] / gcd(m[i][j], m[i - 1][j]) * m[i - 1][j];
                if (j != 1) m[i][j] = m[i][j] / gcd(m[i][j], m[i][j - 1]) * m[i][j - 1];
                if (i != n) m[i][j] = m[i][j] / gcd(m[i][j], m[i + 1][j]) * m[i + 1][j];
                if (j != n) m[i][j] = m[i][j] / gcd(m[i][j], m[i][j + 1]) * m[i][j + 1];
                m[i][j]++;
            }
        }
    }

    return m;
}

std::vector<std::vector<long long>> generateInput() {
    return baseline(1000);
}