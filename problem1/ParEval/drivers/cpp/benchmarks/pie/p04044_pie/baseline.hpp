#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct strstrstr {
    string s;
};

bool cmp(struct strstrstr &a, struct strstrstr &b) {
    return a.s < b.s;
}

vector<string> baseline(int n, int l, vector<string>& inputStrings) {
    vector<strstrstr> t(n);
    for(int i = 0; i < n; i++) {
        t[i].s = inputStrings[i];
    }
    sort(t.begin(), t.end(), cmp);
    vector<string> result;
    for(int i = 0; i < n; i++) {
        result.push_back(t[i].s);
    }
    return result;
}

vector<string> generateInput(int n, int l) {
    vector<string> inputStrings(n);
    for(int i = 0; i < n; i++) {
        inputStrings[i] = string(l, 'a' + (i % 26));
    }
    return inputStrings;
}