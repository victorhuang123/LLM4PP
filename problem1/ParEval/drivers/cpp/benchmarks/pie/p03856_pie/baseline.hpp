#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<string> generateInput() {
    // Generate a large string to maximize the problem scale
    string s;
    for (int i = 0; i < 100000; ++i) {
        s += "dream";
    }
    return {s};
}

bool baseline(const string& s) {
    vector<string> pat = {"dream", "dreamer", "erase", "eraser"};
    vector<bool> f(s.length() + 1, false);
    f[0] = true;

    for (int i = 1; i <= s.length(); i++) {
        for (const auto& p : pat) {
            if (i >= p.length() && s.substr(i - p.length(), p.length()) == p && f[i - p.length()]) {
                f[i] = true;
            }
        }
    }

    return f[s.length()];
}