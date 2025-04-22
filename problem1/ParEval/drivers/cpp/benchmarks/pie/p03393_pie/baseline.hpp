#pragma once

#include <vector>
#include <algorithm>
#include <string>

using namespace std;

string baseline(const string& s) {
    int arr[26] = {0};
    for (char c : s) {
        arr[c - 'a']++;
    }

    if (s == "zyxwvutsrqponmlkjihgfedcba") {
        return "-1";
    }

    if (s.size() <= 25) {
        string result = s;
        for (int i = 0; i < 26; ++i) {
            if (arr[i] != 1) {
                result += (char)('a' + i);
                return result;
            }
        }
    } else {
        vector<char> can;
        int i = 25;
        can.push_back(s[s.size() - 1]);
        while (i > 0 && s[i - 1] > s[i]) {
            i--;
            can.push_back(s[i]);
        }
        i--;
        sort(can.begin(), can.end());
        for (char c : can) {
            if (s[i] < c) {
                return s.substr(0, i) + c;
            }
        }
    }
    return "";
}

string generateInput() {
    return "zyxwvutsrqponmlkjihgfedcba";
}