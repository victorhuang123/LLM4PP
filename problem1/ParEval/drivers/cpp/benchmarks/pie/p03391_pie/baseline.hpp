#pragma once

#include <algorithm>
#include <vector>
#include <utility>
#include <climits>

using namespace std;

long long baseline(int t, vector<pair<long long, long long>>& pairs) {
    long long sum = 0;
    int flag = 0;
    long long minn = LLONG_MAX;

    for (long long i = 0; i < t; i++) {
        long long n = pairs[i].first;
        long long m = pairs[i].second;
        sum += n;
        if (n > m) {
            minn = min(m, minn);
        }
        if (n != m) {
            flag = 1;
        }
    }

    if (!flag) {
        return 0;
    } else {
        return sum - minn;
    }
}

vector<pair<long long, long long>> generateInput(int t) {
    vector<pair<long long, long long>> pairs(t);
    for (int i = 0; i < t; i++) {
        pairs[i] = make_pair(1000000000LL, 999999999LL);
    }
    return pairs;
}