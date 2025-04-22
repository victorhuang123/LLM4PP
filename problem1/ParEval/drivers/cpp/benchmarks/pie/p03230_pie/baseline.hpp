#pragma once

#include <vector>
#include <string>

using namespace std;

string baseline(int n) {
    int k;
    for(k = 1; k * (k - 1) <= 2 * n; k++);
    k--;

    if(k * (k - 1) == 2 * n) {
        string result = "Yes\n" + to_string(k) + "\n";
        vector<vector<int>> v(k + 1);
        int c = 0;
        for(int i = 1; i <= k; i++) {
            for(int j = i + 1; j <= k; j++) {
                v[i].push_back(++c);
                v[j].push_back(c);
            }
        }
        for(int i = 1; i <= k; i++) {
            result += to_string(v[i].size()) + " ";
            for(int j : v[i]) {
                result += to_string(j) + " ";
            }
            result += "\n";
        }
        return result;
    } else {
        return "No";
    }
}