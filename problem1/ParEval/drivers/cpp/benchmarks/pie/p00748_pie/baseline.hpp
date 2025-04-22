#pragma once

#include <vector>

int baseline(int n) {
    const int N = 1000000;
    std::vector<int> all(N + 1, N + 1);
    std::vector<int> odd(N + 1, N + 1);
    std::vector<int> pollock(1000);
    int num;

    all[0] = odd[0] = 0;

    for (num = 1; ; num++) {
        int tmp = num * (num + 1) * (num + 2) / 6;
        if (tmp > N) break;
        pollock[num - 1] = tmp;
    }
    num--;

    auto BackTrack = [&](int n, int type, auto&& BackTrack) -> int {
        if (type && odd[n] <= N) return odd[n];
        if (!type && all[n] <= N) return all[n];

        int ans = N + 1;
        for (int i = num - 1; i >= 0; i--) {
            if (pollock[i] > n) continue;
            if (type && !(pollock[i] & 1)) continue;
            int tmp = BackTrack(n - pollock[i], type, BackTrack);
            if (ans > tmp + 1) ans = tmp + 1;
        }

        if (type) odd[n] = ans;
        if (!type) all[n] = ans;
        return ans;
    };

    return BackTrack(n, 0, BackTrack) + BackTrack(n, 1, BackTrack);
}

std::vector<int> generateInput() {
    return {1000000};
}