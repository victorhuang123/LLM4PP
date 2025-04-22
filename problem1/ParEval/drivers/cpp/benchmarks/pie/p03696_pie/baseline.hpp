#pragma once

#include <string>
using namespace std;

string baseline(long long N, const string& s) {
    long long left = 0;
    long long right = 0;
    string ans;

    for(int i = 0; i < N; i++) {
        if(s[i] == '(') left++;
        if(s[i] == ')') right++;
        if(right > left) {
            right = left;
            ans.push_back('(');
        }
    }

    ans += s;
    right = 0;
    left = 0;

    for(int i = 0; i < ans.size(); i++) {
        if(ans[i] == '(') left++;
        if(ans[i] == ')') right++;
    }

    for(int i = 0; i < left - right; i++) ans.push_back(')');

    return ans;
}

string generateInput() {
    string s;
    for(int i = 0; i < 1000000; i++) {
        if(i % 2 == 0) s.push_back('(');
        else s.push_back(')');
    }
    return s;
}