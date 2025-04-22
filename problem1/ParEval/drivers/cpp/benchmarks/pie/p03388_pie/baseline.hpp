#pragma once

#include <bits/stdc++.h>

using namespace std;

int check(int x, int b) {
    int l = 1, r = x;
    while (r - l > 2) {
        int md1 = l + (r - l + 1) / 3, md2 = r - (r - l + 1) / 3;
        if (md1 * (b + x - md1 + 1) > md2 * (b + x - md2 + 1))
            r = md2;
        else
            l = md1;
    }
    int ans = l * (b + x - l + 1);

    for (int i = l; i <= r; i++)
        ans = max(ans, i * (b + x - i + 1));

    return ans;
}

int baseline(int a, int b) {
    if (a < b)
        swap(a, b);
    int l = 1, r = b;

    while (r - l > 1) {
        int md = (l + r) >> 1;
        if ((a + 1) * md < a * b)
            l = md;
        else
            r = md;
    }
    int left = b - l - 1;

    l = 0, r = a - left;

    while (r - l > 1) {
        int md = (l + r) >> 1;
        if (check(md, b) < a * b)
            l = md;
        else
            r = md;
    }
    return l + b - 1;
}

vector<int> generateInput() {
    return {1000000000000000000LL, 1000000000000000000LL};
}