#pragma once

#include <vector>
#include <algorithm>

using namespace std;

long long baseline(const vector<long long>& numbers) {
    if (numbers.empty()) return 0;
    long long s = numbers[0];
    for (size_t i = 1; i < numbers.size(); ++i) {
        long long x = s, y = numbers[i];
        while (y != 0) {
            long long c = x % y;
            x = y;
            y = c;
        }
        s = x;
    }
    return s;
}

vector<long long> generateInput() {
    vector<long long> numbers(1000000, 1);
    for (long long i = 0; i < 1000000; ++i) {
        numbers[i] = i + 1;
    }
    return numbers;
}