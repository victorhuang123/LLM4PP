#pragma once

#include <algorithm>
#include <functional>
#include <set>
#include <vector>
#include <string>

std::string baseline(int n, const std::vector<int>& inputArray) {
    std::multiset<int, std::greater<int>> S, T;

    for (int i = 0; i < (1 << n); i++) {
        S.insert(inputArray[i]);
    }

    T.insert(*(S.begin()));
    S.erase(S.begin());

    for (int i = 0; i < n; i++) {
        std::vector<int> tmp;
        auto itr = S.begin();
        for (int x : T) {
            while (itr != S.end() && *itr == x) ++itr;
            if (itr == S.end()) {
                return "No";
            }
            tmp.push_back(*itr);
            itr = S.erase(itr);
        }
        if (i != n - 1) T.insert(tmp.begin(), tmp.end());
    }

    return "Yes";
}

std::vector<int> generateInput(int n) {
    std::vector<int> inputArray(1 << n);
    for (int i = 0; i < (1 << n); i++) {
        inputArray[i] = i + 1;
    }
    return inputArray;
}