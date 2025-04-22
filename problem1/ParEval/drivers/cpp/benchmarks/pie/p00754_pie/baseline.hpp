#pragma once

#include <stack>
#include <string>
#include <vector>

using namespace std;

string baseline(const string& line) {
    stack<char> s;
    const int N = line.size();
    bool ok = true;

    for (int i = 0; i < N; ++i) {
        if ((line[i] == '[') || (line[i] == '(')) {
            s.push(line[i]);
        } else if (line[i] == ']') {
            if (s.size() && s.top() == '[') {
                s.pop();
            } else {
                ok = false; break;
            }
        } else if (line[i] == ')') {
            if (s.size() && s.top() == '(') {
                s.pop();
            } else {
                ok = false; break;
            }
        }
    }

    if (s.size()) ok = false;

    return ok ? "yes" : "no";
}

string generateInput() {
    string input;
    for (int i = 0; i < 1000000; ++i) {
        if (i % 2 == 0) {
            input += '[';
        } else {
            input += ']';
        }
    }
    return input;
}