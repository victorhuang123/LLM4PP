#pragma once

#include <vector>

using LL = long long;

LL baseline(int n) {
    LL ans = 0, b;
    std::vector<int> prime;
    std::vector<bool> not_prime(10010, false);

    auto linear_shaker = [&](int x) {
        for (int i = 2; i <= x; i++) {
            if (!not_prime[i]) prime.push_back(i);
            for (size_t j = 0; j < prime.size() && prime[j] * i <= x; j++) {
                not_prime[prime[j] * i] = true;
                if (i % prime[j] == 0) break;
            }
        }
    };

    linear_shaker(10000);

    for (int i = 1; i <= n; i++) {
        int x = i;
        b = 1;
        for (size_t j = 0; j < prime.size() && prime[j] * prime[j] <= x; j++) {
            int cnt = 0;
            if (x % prime[j] == 0) {
                while (x % prime[j] == 0) {
                    x /= prime[j];
                    cnt++;
                }
                b *= (cnt + 1);
            }
        }
        if (x > 1) b *= 2;
        ans += b * i;
    }

    return ans;
}

std::vector<int> generate_input() {
    return {1000000};  // Example input to maximize problem scale
}