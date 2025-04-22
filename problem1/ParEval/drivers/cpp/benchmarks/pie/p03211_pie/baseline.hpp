#pragma once

#include <vector>
#include <string>
#include <cmath>

using namespace std;

int baseline(const string& s) {
    int q = 753;
    for (int i = 2; i < s.size(); i++) {
        int ans = (s[i-2] - '0') * 100;
        ans += (s[i-1] - '0') * 10;
        ans += (s[i] - '0');
        ans = abs(ans - 753);
        if (ans < q)
            q = ans;
    }
    return q;
}

string generateInput() {
    string s(1000000, '9');
    return s;
}