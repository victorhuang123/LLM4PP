#pragma once

#include <vector>
#include <map>

using namespace std;

typedef long long ll;

ll baseline(ll n, const vector<ll>& a_vec) {
    map<ll, ll> iro;
    bool flag = false;
    ll cnt = 0;
    ll ziyuu = 0;
    ll sum = 0;

    for (int i = 0; i < n; i++) {
        iro[a_vec[i]]++;
    }

    while (cnt < 3200) {
        for (int i = 0; i < 400; i++) {
            if (iro[cnt]) {
                flag = true;
            }
            cnt++;
        }
        if (flag) {
            sum++;
        }
        flag = false;
    }

    while (cnt < 5000) {
        for (int i = 0; i <= 2000; i++) {
            ziyuu += iro[cnt];
            cnt++;
        }
    }

    if (sum == 0 && ziyuu > 0) {
        return 1;
    } else {
        return sum + ziyuu;
    }
}

vector<ll> generateInput() {
    vector<ll> a_vec(1000000, 1); // Large input to test efficiency
    return a_vec;
}