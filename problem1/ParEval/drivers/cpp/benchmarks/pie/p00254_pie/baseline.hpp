#pragma once

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

int baseline(int x) {
    if (x % 1111 == 0) {
        return -1; // Represents "NA"
    } else {
        int ans = 0;
        string s;
        int a, b;
        while (x != 6174) {
            stringstream ss;
            ss << x;
            ss >> s;
            s.resize(4, '0');
            sort(s.begin(), s.end());
            stringstream ss1(s);
            ss1 >> a;
            reverse(s.begin(), s.end());
            stringstream ss2(s);
            ss2 >> b;
            x = b - a;
            ans++;
        }
        return ans;
    }
}

vector<int> generateInput() {
    vector<int> inputs;
    for (int i = 0; i < 10000; ++i) {
        inputs.push_back(i);
    }
    return inputs;
}