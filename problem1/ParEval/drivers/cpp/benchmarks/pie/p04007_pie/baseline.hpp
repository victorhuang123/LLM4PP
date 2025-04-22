#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<vector<char>> baseline(int n, int m, vector<vector<char>> ch) {
    vector<vector<char>> chr(n, vector<char>(m));
    vector<vector<char>> chb(n, vector<char>(m));

    chb = ch;
    chr = ch;

    for (int i = 1; i <= m; i++)
        chr[0][i - 1] = chb[n - 1][i - 1] = '#';

    for (int i = 2; i < n; i++)
        chr[i - 1][m - 1] = chb[i - 1][0] = '#';

    for (int i = 2; i < n; i += 2)
        for (int j = 2; j < m; j++)
            chr[i - 1][j - 1] = '#';

    for (int i = 3; i < n; i += 2)
        for (int j = 2; j < m; j++)
            chb[i - 1][j - 1] = '#';

    vector<vector<char>> result;
    result.insert(result.end(), chr.begin(), chr.end());
    result.insert(result.end(), chb.begin(), chb.end());

    return result;
}

vector<vector<char>> generateInput(int n, int m) {
    vector<vector<char>> ch(n, vector<char>(m, '.'));
    return ch;
}