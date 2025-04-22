#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int n, vector<vector<char>>& str) {
    vector<vector<int>> masu(n + 2, vector<int>(n + 2, 0));
    vector<vector<int>> ura(n + 2, vector<int>(n + 2, 0));

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (str[i][j - 1] == '.') {
                ura[i][j] = 0;
            } else {
                ura[i][j] = 1;
            }
        }
    }

    int maxi = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (ura[i][j] == 0) {
                masu[i][j] = min({masu[i - 1][j], masu[i][j - 1], masu[i - 1][j - 1]}) + 1;
                maxi = max(masu[i][j], maxi);
            }
        }
    }

    return maxi;
}

vector<vector<char>> generateInput(int n) {
    vector<vector<char>> str(n + 2, vector<char>(n + 2, '#'));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            str[i][j] = '.';
        }
    }
    return str;
}