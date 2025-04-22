#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

typedef int ll;

string baseline(int n, vector<string>& tmp) {
    vector<string> s;
    vector<vector<string>> dp(1 << n, vector<string>(n, ""));

    for (int i = 0; i < n; i++) {
        bool unique = true;
        for (int j = 0; j < i; j++) {
            if (tmp[j] == tmp[i]) {
                unique = false;
                break;
            }
        }
        if (unique) {
            bool notSubstring = true;
            for (int j = 0; j < n; j++) {
                if (i != j && tmp[j].find(tmp[i]) != string::npos) {
                    notSubstring = false;
                    break;
                }
            }
            if (notSubstring) {
                s.push_back(tmp[i]);
            }
        }
    }

    n = s.size();
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = s[i];
    }

    string ans = "";
    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
            if (!(i & (1 << j))) {
                for (int k = 0; k < n; k++) {
                    if (i & (1 << k)) {
                        string combined = s[j];
                        size_t pos = combined.find(s[k]);
                        if (pos == string::npos) {
                            combined += s[k];
                        } else {
                            combined = combined.substr(0, pos) + s[k];
                        }
                        if (dp[i | (1 << j)][j].empty() || combined.size() < dp[i | (1 << j)][j].size() || (combined.size() == dp[i | (1 << j)][j].size() && combined < dp[i | (1 << j)][j])) {
                            dp[i | (1 << j)][j] = combined;
                        }
                    }
                }
            }
            if (i == (1 << n) - 1) {
                if (ans.empty() || dp[i][j].size() < ans.size() || (dp[i][j].size() == ans.size() && dp[i][j] < ans)) {
                    ans = dp[i][j];
                }
            }
        }
    }

    return ans;
}

vector<string> generateInput(int n) {
    vector<string> input;
    for (int i = 0; i < n; i++) {
        input.push_back("string" + to_string(i));
    }
    return input;
}