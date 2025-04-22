#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int baseline(int n, int k, const vector<int>& values) {
    int vis[20] = {0};
    for(int i = 0; i < k; ++i) {
        vis[values[i]]++;
    }

    string s;
    for(int i = n;; ++i) {
        stringstream in;
        in << i;
        in >> s;
        bool flag = true;
        for(int j = 0; j < s.size(); ++j) {
            int t = s[j] - '0';
            if(vis[t]) {
                flag = false;
                break;
            }
        }
        if(flag) {
            return i;
        }
    }
}

vector<int> generateInput() {
    int n = 1e6;
    int k = 10;
    vector<int> values = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    return values;
}