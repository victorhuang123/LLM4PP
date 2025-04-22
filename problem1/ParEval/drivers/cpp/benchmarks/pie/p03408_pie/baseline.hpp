#pragma once

#include <vector>
#include <string>
#include <map>

using namespace std;

int baseline(int a, const vector<string>& addStrings, const vector<string>& removeStrings) {
    map<string, int> mp;
    int max = 0;

    for (const auto& s : addStrings) {
        mp[s]++;
    }

    for (const auto& s : removeStrings) {
        mp[s]--;
    }

    for (const auto& it : mp) {
        if (it.second > max) {
            max = it.second;
        }
    }

    return max;
}

vector<string> generateInput(int size) {
    vector<string> input(size);
    for (int i = 0; i < size; ++i) {
        input[i] = "string" + to_string(i % 1000);
    }
    return input;
}