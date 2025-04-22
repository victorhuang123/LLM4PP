#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(const string& ss) {
    stack<char> Q;
    map<char,int> mp; 
    int tot = 0, num = 0, t;
    int i = 0;
    int j = ss.size() - 1;
    while(i <= j) {
        if(ss[i] == ss[j]) {
            i++;
            j--;
            continue;
        }
        if(ss[i] == 'x') {
            i++;
            tot++;
            continue;
        }
        if(ss[j] == 'x') {
            j--;
            tot++;
            continue;
        } else {
            return -1;
        }
    }
    return tot;
}

string generateInput() {
    string s(1000000, 'x');
    s[500000] = 'a';
    return s;
}