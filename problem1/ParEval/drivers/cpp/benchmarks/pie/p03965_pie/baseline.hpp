#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(const vector<char>& a) {
    int x = 0, y = 0;
    int ans = 0;
    for (size_t i = 0; i < a.size(); i++) {
        if (x == y) {
            x++;
            if (a[i] == 'p') ans--;
        } else {
            y++;
            if (a[i] == 'g') ans++;
        }
    }
    return ans;
}

vector<char> generateInput() {
    vector<char> input(1000000, 'g');
    for (int i = 0; i < 500000; i++) {
        input[i] = 'p';
    }
    return input;
}