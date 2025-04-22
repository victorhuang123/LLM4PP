#pragma once

#include <vector>
#include <stack>
#include <string>

using namespace std;

int baseline(int a, const string& str) {
    stack<char> S;
    S.push(str[0]);
    int cnt = 1;
    for(int i = 1; i < a; i++) {
        if(str[i] == S.top()) continue;
        else {
            cnt++;
            S.push(str[i]);
        }
    }
    return cnt;
}

string generateInput() {
    string str;
    for (int i = 0; i < 1000000; ++i) {
        str += (i % 2 == 0) ? 'A' : 'B';
    }
    return str;
}