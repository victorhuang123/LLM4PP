#pragma once

#include<vector>
#include<utility>

using namespace std;

vector<int> baseline(int n, const vector<pair<int, int>>& input) {
    static int aizu[200300] = {0};
    vector<int> result;
    for (int i = 0; i < n; i++) {
        int a = input[i].first;
        int b = input[i].second;
        aizu[a + b]++;
    }
    for (int i = 0; i < 200279; i++) {
        aizu[i + 1] += aizu[i] / 2;
        aizu[i] %= 2;
        if (aizu[i] == 1) {
            result.push_back(i);
        }
    }
    return result;
}

vector<pair<int, int>> generateInput(int n) {
    vector<pair<int, int>> input;
    for (int i = 0; i < n; i++) {
        input.push_back(make_pair(i, i + 1));
    }
    return input;
}