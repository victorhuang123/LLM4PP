#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

vector<string> generateInput(int n) {
    vector<string> s(n);
    for (int i = 0; i < n; i++) {
        s[i] = (i % 3 == 0) ? "AB" : (i % 3 == 1) ? "AC" : "BC";
    }
    return s;
}

bool baseline(int n, int a, int b, int c, const vector<string>& s) {
    vector<char> ans(n);
    function<bool(int, int, int, int)> dfs = [&](int id, int a, int b, int c) -> bool {
        if (a < 0 || b < 0 || c < 0) return false;

        if (id == n) {
            return true;
        } else {
            if (s[id] == "AB") {
                ans[id] = 'A';
                if (dfs(id + 1, a + 1, b - 1, c)) return true;
                ans[id] = 'B';
                if (dfs(id + 1, a - 1, b + 1, c)) return true;
            } else if (s[id] == "AC") {
                ans[id] = 'A';
                if (dfs(id + 1, a + 1, b, c - 1)) return true;
                ans[id] = 'C';
                if (dfs(id + 1, a - 1, b, c + 1)) return true;
            } else if (s[id] == "BC") {
                ans[id] = 'B';
                if (dfs(id + 1, a, b + 1, c - 1)) return true;
                ans[id] = 'C';
                if (dfs(id + 1, a, b - 1, c + 1)) return true;
            }
        }
        return false;
    };

    return dfs(0, a, b, c);
}