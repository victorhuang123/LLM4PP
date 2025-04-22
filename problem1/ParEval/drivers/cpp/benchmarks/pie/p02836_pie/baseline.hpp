#pragma once

#include <string>
#include <vector>

using namespace std;

int baseline(const string& s) {
    int n = s.length(), c = 0;
    for (int i = 0; i < n / 2; i++) {
        if (s[i] != s[n - i - 1])
            c++;
    }
    return c;
}

string generateInput() {
    string s;
    for (int i = 0; i < 1000000; i++) {
        s += (i % 2 == 0) ? 'a' : 'b';
    }
    return s;
}