#pragma once

#include<bits/stdc++.h>

using namespace std;

string baseline(string a, string b) {
    int al = a.length(), bl = b.length();
    vector<vector<int>> dp(al+1, vector<int>(bl+1, 0));
    for(int i = 0; i <= al; i++) {
        for(int j = 0; j <= bl; j++) {
            if(i == 0 || j == 0)
                dp[i][j] = 0;
            else if(a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1] + 1;
            else
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
        }
    }
    int index = dp[al][bl];
    string l = "";
    int i = al, j = bl;
    while(i > 0 && j > 0) {
        if(a[i-1] == b[j-1]) {
            l += a[i-1];
            i--, j--, index--;
        }
        else if(dp[i-1][j] > dp[i][j-1]) {
            i--;
        }
        else {
            j--;
        }
    }
    reverse(l.begin(), l.end());
    return l;
}

vector<string> generateInput() {
    string a(10000, 'a');
    string b(10000, 'b');
    return {a, b};
}