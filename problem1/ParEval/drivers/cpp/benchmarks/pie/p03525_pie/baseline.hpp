#pragma once

#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define pp pop_back
#define all(s) s.begin(), s.end()

const int inf = (int)1e9 + 7;

int baseline(int n, vector<int>& d) {
    int ans = 0;

    function<void(int, vector<int>)> go = [&](int in, vector<int> vec) {
        if (in == n + 1) {
            int dif = inf;
            sort(all(vec));
            for (int i = 0; i < n; i++) {
                for (int j = i + 1; j <= n; j++) {
                    int q1 = vec[i];
                    int q2 = vec[j];
                    q2 -= q1;
                    q1 = 0;
                    dif = min(dif, min(q2, 24 - q2));
                }
            }
            ans = max(ans, dif);
            if (clock() > CLOCKS_PER_SEC * 1.5) {
                return;
            }
            return;
        }
        vec.pb(d[in]);
        go(in + 1, vec);
        vec.pp();

        vec.pb(24 - d[in]);
        go(in + 1, vec);
    };

    vector<int> vec;
    vec.pb(0);
    go(1, vec);
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> d(n + 1);
    d[0] = 0;
    for (int i = 1; i <= n; i++) {
        d[i] = i;
    }
    return d;
}