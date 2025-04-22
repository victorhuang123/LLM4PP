#pragma once

#include<vector>
#include<algorithm>
#include<cstring>

long long baseline(int n, const std::vector<std::vector<int>>& f, const std::vector<std::vector<long long>>& p) {
    std::vector<int> way(n, 0);
    long long ans = 0, re;

    for (int t = 1023; t; t--) {
        re = 0;
        int temp = t;
        std::fill(way.begin(), way.end(), 0);

        for (int i = 0; i < 10; i++) {
            if (temp & 1) {
                for (int j = 0; j < n; j++) {
                    if (f[j][i])
                        way[j] += 1;
                }
            }
            temp >>= 1;
        }

        for (int i = 0; i < n; i++)
            re += p[i][way[i]];

        if (t == 1023)
            ans = re;
        else if (re > ans)
            ans = re;
    }

    return ans;
}

std::pair<std::vector<std::vector<int>>, std::vector<std::vector<long long>>> generateInput() {
    int n = 100;
    std::vector<std::vector<int>> f(n, std::vector<int>(10, 1));
    std::vector<std::vector<long long>> p(n, std::vector<long long>(11, 1));

    return {f, p};
}