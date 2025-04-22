#pragma once

#include <vector>
using namespace std;

long long baseline(const vector<long long>& num) {
    long long min1 = num[0];
    long long sum = 0;
    for (size_t i = 1; i < num.size(); i++) {
        if (num[i] < min1) {
            sum++;
            min1 = num[i];
        }
    }
    return sum + 1;
}

vector<long long> generateInput() {
    vector<long long> num(1000000);
    for (long long i = 0; i < 1000000; i++) {
        num[i] = 1000000 - i;
    }
    return num;
}