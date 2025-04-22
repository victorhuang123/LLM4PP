#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

vector<vector<int>> generate_input(int n) {
    vector<vector<int>> input(3, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        input[0][i] = i;
        input[1][i] = i;
        input[2][i] = i;
    }
    return input;
}

ll baseline(int n, vector<int>& a, vector<int>& b, vector<int>& c) {
    vector<vector<ll>> ans(n, vector<ll>(2, 0));
    ll A = 0;

    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    sort(c.begin(), c.end());

    for(int i = 0; i < n; i++) {
        int s = 0, e = n - 1, m, loc = -1;
        while(s <= e) {
            m = (s + e) / 2;
            if(a[m] < b[i]) {
                loc = m;
                s = m + 1;
            } else {
                e = m - 1;
            }
        }
        ans[i][0] = loc + 1;
    }

    for(int i = 1; i < n; i++) {
        ans[i][0] += ans[i - 1][0];
    }

    for(int i = 0; i < n; i++) {
        int s = 0, e = n - 1, m, loc = -1;
        while(s <= e) {
            m = (s + e) / 2;
            if(b[m] < c[i]) {
                loc = m;
                s = m + 1;
            } else {
                e = m - 1;
            }
        }
        if(loc != -1) {
            ans[i][1] = ans[loc][0];
        }
    }

    for(int i = 0; i < n; i++) {
        A += ans[i][1];
    }

    return A;
}