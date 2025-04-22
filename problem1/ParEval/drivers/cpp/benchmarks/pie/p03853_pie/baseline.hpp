#pragma once

#include <vector>
#include <string>

using namespace std;

string baseline(int h, int w) {
    vector<vector<char>> str(h, vector<char>(w));
    string result;

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> str[i][j];
        }
    }

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            result += str[i][j];
        }
        result += '\n';
        for (int j = 0; j < w; j++) {
            result += str[i][j];
        }
        result += '\n';
    }

    return result;
}

vector<vector<char>> generateInput(int h, int w) {
    vector<vector<char>> input(h, vector<char>(w));
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            input[i][j] = 'a' + (i + j) % 26;
        }
    }
    return input;
}