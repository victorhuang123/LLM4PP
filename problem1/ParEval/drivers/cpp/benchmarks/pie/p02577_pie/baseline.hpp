#pragma once

#include <string>
using namespace std;

string baseline(const string& x) {
    long long s = 0;
    for (size_t i = 0; i < x.size(); i++) {
        s += (x[i] - '0');
        s %= 9;
    }
    if (s % 9 == 0)
        return "Yes";
    else
        return "No";
}

string generateInput() {
    return string(1000000, '9');
}