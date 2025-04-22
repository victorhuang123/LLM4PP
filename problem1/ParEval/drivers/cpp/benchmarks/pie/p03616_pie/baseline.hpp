#pragma once

#include<bits/stdc++.h>

struct ev {
    int x, y, id;
    bool operator<(const ev& e) const { return x < e.x; }
};

std::vector<int> baseline(int X, int k, int q, const std::vector<int>& a_list, const std::vector<std::pair<int, int>>& queries) {
    std::vector<ev> e;
    std::vector<int> results(q);

    for (int i = 0; i < k; ++i) {
        e.push_back({a_list[i], 0, 0});
    }

    for (int i = 0; i < q; ++i) {
        e.push_back({queries[i].first, queries[i].second, i + 1});
    }

    std::sort(e.begin(), e.end());

    long long mn = 0, mx = X, a = 0;
    int sgn = -1, t0 = 0;

    for (const auto& event : e) {
        long long v0 = (event.x - t0) * sgn;

        if (event.id) {
            long long v = event.y + a;
            v = std::max(mn, std::min(mx, v));
            v += v0;
            v = std::max(0LL, std::min(static_cast<long long>(X), v));
            results[event.id - 1] = v;
        } else {
            mn += v0;
            mx += v0;
            a += v0;
            mn = std::max(0LL, mn);
            mx = std::max(0LL, mx);
            mx = std::min(static_cast<long long>(X), mx);
            mn = std::min(static_cast<long long>(X), mn);
            t0 = event.x;
            sgn *= -1;
        }
    }

    return results;
}

std::tuple<int, int, int, std::vector<int>, std::vector<std::pair<int, int>>> generate_input() {
    int X = 1e9;
    int k = 1e5;
    int q = 1e5;
    std::vector<int> a_list(k);
    std::vector<std::pair<int, int>> queries(q);

    for (int i = 0; i < k; ++i) {
        a_list[i] = rand() % X;
    }

    for (int i = 0; i < q; ++i) {
        queries[i] = {rand() % X, rand() % X};
    }

    return {X, k, q, a_list, queries};
}