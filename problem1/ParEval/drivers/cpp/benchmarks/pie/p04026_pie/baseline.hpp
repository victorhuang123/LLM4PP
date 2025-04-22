#pragma once

#include <map>
#include <string>
#include <vector>

using namespace std;

#define FOR(i,a,b) for(int i=(a);i<(b);++i)
#define REP(i,n) FOR(i,0,n)

const int MAX_N = 1e5;

string generate_input() {
    string s(MAX_N, 'a');
    FOR(i, 1, MAX_N) {
        s[i] = 'a' + (i % 26);
    }
    return s;
}

pair<int, int> baseline(const string& s) {
    vector<map<char, int>> occurrence(MAX_N + 1);

    REP(i, s.length()) {
        REP(j, 26) {
            occurrence[i+1]['a' + j] = occurrence[i]['a' + j];
        }
        occurrence[i+1][s[i]] = occurrence[i][s[i]] + 1;
    }

    REP(a, s.length()) {
        if (a+1 < s.length() && s[a] == s[a+1]) {
            return {a + 1, a + 2};
        } else if (a+2 < s.length() && s[a] == s[a+2]) {
            return {a + 1, a + 3};
        }
    }
    return {-1, -1};
}