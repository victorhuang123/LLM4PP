#pragma once

#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int baseline(string s) {
    int ls = s.size(), ans = ls;
    for (int i = 1; i < ls; ++i) if (s[i - 1] != s[i]) ans = min(ans, max(i, ls - i));
    return ans;
}

string generateInput() {
    return string(100000, 'a') + string(100000, 'b');
}