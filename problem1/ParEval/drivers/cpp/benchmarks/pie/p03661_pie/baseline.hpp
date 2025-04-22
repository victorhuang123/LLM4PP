#pragma once

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

typedef long long ll;

vector<ll> generateInput() {
    int length = 200000;
    vector<ll> arr(length, 1);
    return arr;
}

ll baseline(const vector<ll>& arr) {
    int length = arr.size();
    vector<ll> res(length, 0);
    ll temp = 0;
    ll m = LLONG_MAX;

    res[0] = arr[0];
    for (int i = 1; i < length; ++i) {
        res[i] = res[i - 1] + arr[i];
    }

    for (int i = 1; i < length; ++i) {
        temp = abs(res[length - 1] - res[i - 1] * 2);
        m = min(temp, m);
    }

    return m;
}