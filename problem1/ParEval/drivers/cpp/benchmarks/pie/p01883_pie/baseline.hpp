#pragma once

#include <string>
#include <vector>

using namespace std;

string baseline(int n) {
    string s = "";
    int now = 1;

    while (n > 0) {
        if (now >= n) {
            int cur = now;
            while (cur > n) {
                s = ')' + s;
                cur--;
            }
            s = '(' + s;
            while (cur > 0) {
                s = ')' + s;
                cur--;
            }
            n = 0;
        } else {
            s = '(' + s;
            n -= now;
        }
        now++;
    }

    return s;
}

vector<int> generateInput() {
    return {1000000}; // Example input to maximize the problem scale
}