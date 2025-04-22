#pragma once

#include<map>
#include<vector>
#include<algorithm>
using namespace std;

vector<int> generate_input(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; ++i) {
        input[i] = i + 1;
    }
    return input;
}

int baseline(const vector<int>& input) {
    map<int, int> mp;
    int now = 1, cnt = 0;
    for (int x : input) {
        if (x < now) {
            continue;
        }
        while (mp[x] > 0 && x > 0) {
            mp[x] = 0;
            x--;
            cnt--;
        }
        mp[x] = 1;
        cnt++;
        while (mp[now] > 0 && now < 500010) {
            now++;
        }
        now = min(now, cnt);
        if (x == 0) {
            now = 1e9;
        }
    }
    return now;
}