#pragma once

#include <vector>
#include <string>

using namespace std;

vector<string> generate_input() {
    vector<string> inputs;
    for (int i = 0; i < 1000000; ++i) {
        inputs.push_back("aabbcc");
    }
    return inputs;
}

string baseline(const string& s) {
    if (s.size() != 6) {
        return "No";
    }
    if (s[2] == s[3] && s[4] == s[5]) {
        return "Yes";
    } else {
        return "No";
    }
}