#pragma once

#include <vector>
#include <string>

using namespace std;

int baseline(const vector<string>& X) {
    vector<unsigned int> x(X.size(), 0);
    int next = 0;
    while (true) {
        if (X[next].length() == x[next]) {
            return next;
        }
        x[next]++;
        next = X[next][x[next] - 1] - 'a';
    }
}

vector<string> generateInput() {
    return {
        "abacaba",
        "bacabac",
        "cabacab"
    };
}