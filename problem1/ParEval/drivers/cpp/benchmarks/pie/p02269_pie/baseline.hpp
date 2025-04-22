#pragma once

#include <vector>
#include <string>
#include <cstring>

const int MAXT = 1000003;
const int MAXN = 1000010;

std::vector<bool> baseline(int n, const std::vector<std::string>& operations, const std::vector<std::string>& queries) {
    std::vector<int> head(MAXT, -1);
    std::vector<int> nex(MAXN, -1);
    std::vector<int> to(MAXN, 0);
    int top = 0;
    std::vector<bool> results;

    auto jisuan = [](char c) {
        if (c == 'A') return 1;
        if (c == 'C') return 2;
        if (c == 'G') return 3;
        if (c == 'T') return 4;
        return 0;
    };

    auto insert = [&](int k) {
        nex[top] = head[k % MAXT];
        head[k % MAXT] = top;
        to[top++] = k;
    };

    auto k = [&](const std::string& ss) {
        int s = 1;
        int sum = 0;
        for (char c : ss) {
            sum += s * jisuan(c);
            s *= 5;
        }
        return sum;
    };

    auto ff = [&](int k) {
        int u = head[k % MAXT];
        while (u != -1) {
            if (to[u] == k) return true;
            u = nex[u];
        }
        return false;
    };

    for (int i = 0; i < n; i++) {
        if (operations[i] == "insert") {
            int tmp = k(queries[i]);
            insert(tmp);
        } else {
            int tmp = k(queries[i]);
            results.push_back(ff(tmp));
        }
    }

    return results;
}

std::vector<std::string> generateInput(int n) {
    std::vector<std::string> operations(n);
    std::vector<std::string> queries(n);
    for (int i = 0; i < n; i++) {
        operations[i] = (i % 2 == 0) ? "insert" : "find";
        queries[i] = std::string(10, 'A' + (i % 4));
    }
    return {operations, queries};
}