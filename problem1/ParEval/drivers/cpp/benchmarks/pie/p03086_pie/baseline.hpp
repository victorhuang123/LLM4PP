#pragma once

#include <vector>
#include <string>
#include <regex>
#include <algorithm>

using namespace std;

int baseline(const string& s) {
    int res = 0;
    smatch m;
    for (auto it = cbegin(s); regex_search(it, cend(s), m, regex("[ACGT]+")); it = m[0].second)
        res = max<int>(res, m.str().size());
    return res;
}

string generateInput() {
    string s;
    for (int i = 0; i < 1000000; ++i) {
        s += "ACGT";
    }
    return s;
}