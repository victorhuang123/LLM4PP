#pragma once

#include <bits/stdc++.h>

using namespace std;

string baseline(int w, int h, vector<string>& rows) {
    vector<vector<string>> len(h, vector<string>(w, ""));
    vector<vector<string>> amt(h, vector<string>(w, ""));

    for (int i = h-1; i >= 0; i--) {
        for (int j = w-1; j >= 0; j--) {
            if (rows[i][j] >= 'A') continue;
            if (rows[i][j] == '0') {
                auto ls = { len[i+1][j], len[i][j+1] };
                len[i][j] = "0" + *max_element(ls.begin(), ls.end(), [](const string& a, const string& b) {
                    int d = a.length() - b.length();
                    if (d) return d < 0;
                    return a.compare(b) < 0;
                });

                auto as = { amt[i+1][j], amt[i][j+1] };
                amt[i][j] = *max_element(as.begin(), as.end(), [](const string& a, const string& b) {
                    int d = a.length() - b.length();
                    if (d) return d < 0;
                    return a.compare(b) < 0;
                });
            } else {
                auto ls = { len[i+1][j], len[i][j+1] };
                amt[i][j] = len[i][j] = rows[i][j] + *max_element(ls.begin(), ls.end(), [](const string& a, const string& b) {
                    int d = a.length() - b.length();
                    if (d) return d < 0;
                    return a.compare(b) < 0;
                });
            }
        }
    }

    string ans = "";
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (amt[i][j].compare(ans) > 0) ans = amt[i][j];
        }
    }
    return ans;
}

vector<string> generateInput(int w, int h) {
    vector<string> rows(h, string(w, '0'));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (rand() % 2) rows[i][j] = '1' + rand() % 9;
        }
    }
    return rows;
}