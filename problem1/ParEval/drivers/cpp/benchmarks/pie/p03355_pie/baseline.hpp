#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

string baseline(const string& s, int ii) {
    int n = s.length();
    vector<string> a;
    a.reserve(55555);

    for (int i = 1; i <= 5; i++) {
        for (int k = 0; k + i <= n; k++) {
            a.push_back(s.substr(k, i));
        }
    }

    sort(a.begin(), a.end());
    auto last = unique(a.begin(), a.end());
    a.erase(last, a.end());

    return a[ii - 1];
}

