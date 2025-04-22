#pragma once

#include <vector>
#include <string>
#include <set>

using namespace std;

int baseline(int n, const string& a, const string& b, const string& c) {
    int cou = 0;
    for (int i = 0; i < n; i++) {
        set<char> se;
        se.insert(a[i]);
        se.insert(b[i]);
        se.insert(c[i]);
        cou += se.size() - 1;
    }
    return cou;
}

vector<string> generateInput(int n) {
    string a(n, 'a');
    string b(n, 'b');
    string c(n, 'c');
    return {a, b, c};
}