#pragma once

#include <algorithm>
#include <deque>
#include <stdexcept>
#include <vector>

int baseline(int len, const std::vector<char>& a, const std::vector<char>& b) {
    std::deque<int>::size_type answer = 0;
    std::deque<int> DQ;
    DQ.push_back(len + 1);

    int k = len + 1, offset = 0;
    for (int i = len; i > 0; i--) {
        int t = k;
        k = std::min(i, k);
        while (k && a[k - 1] != b[i - 1])
            k--;
        if (k <= 0)
            throw std::runtime_error("There is no solution under such constraints");

        if (k == t) {
            while (!DQ.empty() && DQ.back() + offset >= i)
                DQ.pop_back();
            DQ.push_back(i - offset);
        } else {
            offset--;
            if (i != k)
                answer = std::max(answer, DQ.size()), DQ.push_front(k - offset);
        }
    }
    return answer;
}

std::vector<char> generateInput(int len, char c) {
    return std::vector<char>(len, c);
}