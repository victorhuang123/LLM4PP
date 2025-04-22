#pragma once

#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

int baseline(ll a, ll b) {
    if (a < 2) a = 2;
    if (!(a < b)) return 0;
    int ans = b - a;
    vector<bool> prime_small(1000100, false);
    vector<int> cnt_pow(b - a, INF);
    for (int i = 2; (ll)i * i < b; i++) {
        if (!prime_small[i]) {
            for (int j = 2 * i; (ll)j * j < b; j += i) prime_small[j] = true;
            for (ll j = max(2LL, (a + i - 1) / i) * i; j < b; j += i) {
                if (cnt_pow[j - a] == -1) continue;
                ll t = j;
                int cnt = 0;
                while (t % i == 0) {
                    t /= i;
                    cnt++;
                }
                if (cnt_pow[j - a] < cnt) {
                    cnt_pow[j - a] = -1;
                    ans--;
                } else {
                    cnt_pow[j - a] = cnt;
                }
            }
        }
    }
    return ans;
}

vector<ll> generateInput() {
    vector<ll> input = {2, 1000000};
    return input;
}