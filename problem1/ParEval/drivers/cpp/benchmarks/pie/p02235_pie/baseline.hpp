#pragma once

#include<vector>
#include<string>
#include<algorithm>

using namespace std;

int baseline(const string& a, const string& b) {
    int lena = a.length();
    int lenb = b.length();
    vector<vector<int>> dp(lena + 1, vector<int>(lenb + 1, 0));
    
    for (int i = 1; i <= lena; i++) {
        for (int j = 1; j <= lenb; j++) {
            if (a[i-1] == b[j-1]) {
                dp[i][j] = dp[i-1][j-1] + 1;
            } else {
                dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
    }
    return dp[lena][lenb];
}

string generateInput(int n) {
    string s(n, 'a');
    for (int i = 0; i < n; i++) {
        s[i] = 'a' + (i % 26);
    }
    return s;
}