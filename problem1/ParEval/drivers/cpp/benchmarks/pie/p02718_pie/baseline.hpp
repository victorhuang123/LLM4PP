#pragma once

#include <vector>
#include <string>

using namespace std;

string baseline(int a, int b, const vector<long long>& x) {
    long double c = 0;
    long double ans = 0;

    for (int i = 0; i < a; i++) {
        c += x[i];
    }

    for (int i = 0; i < a; i++) {
        if (x[i] >= c / 4 / b) {
            ans++;
        }
    }

    if (b <= ans) {
        return "Yes";
    } else {
        return "No";
    }
}

vector<long long> generateInput() {
    return vector<long long>(1000000, 1000000000LL);
}