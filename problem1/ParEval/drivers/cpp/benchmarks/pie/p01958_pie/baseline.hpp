#pragma once

#include <vector>
#include <cmath>

using namespace std;

int baseline(int l, int r) {
    vector<int> a(100010, 0);
    vector<int> prime;
    int cnt = 0;

    a[1] = 1;
    a[0] = 1;

    for (long long i = 2; i <= 100000; i++) {
        if (!a[i]) {
            prime.push_back(i);
            cnt++;
            for (long long j = i * i; j <= 100000; j += i) {
                a[j] = 1;
            }
        }
    }

    int ans = 0;
    for (int i = l; i <= r; i++) {
        int sum = 0, n = i;
        for (int j = 0; prime[j] * prime[j] <= n; j++) {
            while (!(n % prime[j])) {
                n /= prime[j];
                sum++;
            }
        }
        if (n != 1)
            sum++;
        if (!a[sum])
            ans++;
    }
    return ans;
}

vector<int> generateInput() {
    return {1, 100000};
}