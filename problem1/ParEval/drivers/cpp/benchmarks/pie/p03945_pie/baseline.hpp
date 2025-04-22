#pragma once

#include <string>
#include <vector>

using namespace std;

int baseline(const string& s) {
    int ans = 0;
    for (size_t i = 1; i < s.length(); ++i) {
        if (s[i-1] != s[i]) ans++;
    }
    return ans;
}

string generateInput() {
    string s;
    s.reserve(1000000);
    for (int i = 0; i < 1000000; ++i) {
        s += (i % 2 == 0) ? 'a' : 'b';
    }
    return s;
}