#pragma once

#include <vector>
#include <stack>
#include <string>

using namespace std;

int baseline(const string& S) {
    stack<char> ST;

    for (int i = 0; i < S.size(); i++) {
        try {
            if (ST.empty()) throw "empty stack!";
            if (ST.top() != S[i]) ST.pop();
            else                  ST.push(S[i]);
        } catch (const char *error) {
            ST.push(S[i]);
        }
    }

    return S.size() - ST.size();
}

string generateInput() {
    return string(1000000, 'a');
}