#pragma once

#include<vector>
#include<cstring>
#include<algorithm>

std::vector<std::vector<int>> baseline(int n, std::vector<std::string> op, std::vector<int> a, std::vector<bool> c, std::vector<std::vector<int>> b) {
    std::vector<int> bit(n * 2 + 1, 0);
    std::vector<std::vector<int>> f(n + 1, std::vector<int>(n + 1, 0x3f3f3f3f));

    for(int i = 1; i <= n + n; i++) {
        c[i] = (op[i][0] != 'W');
        b[a[i]][c[i]] = i;
    }

    f[0][0] = 0;

    for(int i = 0; i <= n; i++) {
        std::fill(bit.begin(), bit.end(), 0);
        for(int j = 1; j <= n + n; j++) {
            for(int k = j; k <= n + n; k += (k & -k)) bit[k] += 1;
        }
        for(int j = 1; j <= i; j++) {
            for(int k = b[j][0]; k <= n + n; k += (k & -k)) bit[k] -= 1;
        }
        for(int j = 0; j <= n; j++) {
            if(j > 0) {
                for(int k = b[j][1]; k <= n + n; k += (k & -k)) bit[k] -= 1;
            }
            if(i > 0) {
                int sum = 0;
                for(int k = b[i][0]; k; k -= (k & -k)) sum += bit[k];
                f[i][j] = std::min(f[i][j], f[i - 1][j] + sum);
            }
            if(j > 0) {
                int sum = 0;
                for(int k = b[j][1]; k; k -= (k & -k)) sum += bit[k];
                f[i][j] = std::min(f[i][j], f[i][j - 1] + sum);
            }
        }
    }

    return f;
}

std::tuple<std::vector<std::string>, std::vector<int>, std::vector<bool>, std::vector<std::vector<int>>> generateInput(int n) {
    std::vector<std::string> op(n * 2 + 1);
    std::vector<int> a(n * 2 + 1);
    std::vector<bool> c(n * 2 + 1);
    std::vector<std::vector<int>> b(n + 1, std::vector<int>(2));

    for(int i = 1; i <= n * 2; i++) {
        op[i] = (i % 2 == 0) ? "W" : "R";
        a[i] = (i + 1) / 2;
    }

    return {op, a, c, b};
}