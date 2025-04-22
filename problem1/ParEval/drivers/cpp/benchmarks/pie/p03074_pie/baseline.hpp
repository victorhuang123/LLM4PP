#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> generateInput(int n) {
    vector<int> input;
    for (int i = 0; i < n; ++i) {
        input.push_back(rand() % 2);
    }
    return input;
}

int baseline(int n, int k, string s) {
    vector<int> cs(n, 0);
    vector<int> freq(n, -1);

    cs[0] = (s[0] == '0');
    freq[0] += (s[0] == '1');
    int ans = 1;

    for(int i = 1; i < s.size(); i++) {
        if(s[i] == s[i - 1] || s[i] == '1')
            cs[i] = cs[i - 1];
        else
            cs[i] = cs[i - 1] + 1;

        if(cs[i] <= k) {
            ans = i + 1;
        } else {
            if(freq[cs[i] - k] != -1)
                ans = max(ans, i - freq[cs[i] - k] + 1);
        }

        if(s[i] == '1' && freq[cs[i]] == -1) freq[cs[i]] = i;
    }

    return ans;
}