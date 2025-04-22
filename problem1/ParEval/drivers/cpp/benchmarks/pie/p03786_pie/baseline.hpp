#pragma once

#include <algorithm>
#include <vector>

long long baseline(const std::vector<long long>& s1) {
    long long n = s1.size();
    std::vector<long long> sorted_s1 = s1;
    std::sort(sorted_s1.begin(), sorted_s1.end());
    
    std::vector<long long> judgesum(n + 1, 0);
    for (long long a = 1; a <= n; a++) {
        judgesum[a] = judgesum[a - 1] + sorted_s1[a - 1];
    }
    
    long long sum = 1;
    for (long long a = n - 1; a >= 1; a--) {
        if (2 * judgesum[a] >= sorted_s1[a]) {
            sum++;
        } else {
            break;
        }
    }
    return sum;
}

std::vector<long long> generateInput() {
    std::vector<long long> input(100000);
    for (long long i = 0; i < 100000; i++) {
        input[i] = i + 1;
    }
    return input;
}