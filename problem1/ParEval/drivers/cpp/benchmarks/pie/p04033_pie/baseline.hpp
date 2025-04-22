#pragma once

#include<bits/stdc++.h>

using namespace std;

string baseline(long long a, long long b) {
    long long fans = 0;

    if ((a < 0 && b > 0) || a == 0 || b == 0) {
        return "Zero";
    }

    for (int i = a; i <= b; i++) {
        if (i < 0)
            fans++;
    }

    if (fans % 2 == 1)
        return "Negative";
    else
        return "Positive";
}

pair<long long, long long> generateInput() {
    return make_pair(-1000000000, 1000000000);
}