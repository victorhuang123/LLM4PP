#pragma once

#include <map>
#include <vector>
#include <string>

using namespace std;

vector<string> generateInput(int n) {
    vector<string> input;
    for (int i = 0; i < n; ++i) {
        input.push_back("number" + to_string(i));
    }
    return input;
}

vector<string> baseline(int n, map<string, int>& info, vector<string>& seq) {
    string number;
    int a, b;
    bool flag = true;
    vector<string> result;

    while (n--) {
        number = "number" + to_string(n);
        a = 1000;
        b = 1000;
        if (!info[number]) seq.push_back(number);
        while (b-- && info[number] < 1000000) {
            info[number] += a;
        }
    }

    for (int i = 0; i < seq.size(); i++) {
        if (info[seq[i]] >= 1000000) {
            flag = false;
            result.push_back(seq[i]);
        }
    }
    if (flag) result.push_back("NA");
    return result;
}