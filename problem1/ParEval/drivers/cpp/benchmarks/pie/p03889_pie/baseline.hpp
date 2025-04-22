#pragma once

#include<bits/stdc++.h>

using namespace std;

char Chg(char x) {
    return x == 'b' ? 'd' : (x == 'd' ? 'b' : (x == 'p' ? 'q' : 'p'));
}

bool baseline(const string& input) {
    string s = input;
    string ch = input;
    reverse(ch.begin(), ch.end());
    for (char &c : ch) {
        c = Chg(c);
    }
    return s == ch;
}

string generateInput() {
    string input(100000, 'b');
    return input;
}