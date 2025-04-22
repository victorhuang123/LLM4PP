#pragma once

#include <bits/stdc++.h>

#define ll long long
#define str string
#define pb push_back

using namespace std;

ll baseline(const str& s) {
    ll cnt = 0, sum = 0, mx = 0;
    int right1 = s.size() - 1, left1 = 0;

    for (int i = 0; i < (int)s.size(); ++i) {
        if (s[right1] == 'Z' && sum == 0) {
            cnt += (s.size() - 1) - right1;
            sum++;
        }

        if (s[left1] == 'A' && mx == 0) {
            cnt += left1;
            mx++;
        }

        right1--;
        left1++;
    }

    return s.size() - cnt;
}

str generateInput() {
    str s(1e6, 'A');
    s[5e5] = 'Z';
    return s;
}