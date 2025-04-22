#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int baseline(int n, vector<string>& startTimes, vector<string>& endTimes) {
    vector<int> dia(24 * 60 * 60, 0);
    for (int i = 0; i < n; ++i) {
        int start = stoi(startTimes[i].substr(0, 2)) * 60 * 60 + stoi(startTimes[i].substr(3, 2)) * 60 + stoi(startTimes[i].substr(6, 2));
        int goal = stoi(endTimes[i].substr(0, 2)) * 60 * 60 + stoi(endTimes[i].substr(3, 2)) * 60 + stoi(endTimes[i].substr(6, 2));
        for (int j = start; j < goal; ++j) {
            dia[j]++;
        }
    }
    int ans = 0;
    for (int i = 0; i < dia.size(); ++i) {
        ans = max(ans, dia[i]);
    }
    return ans;
}

vector<string> generateInput(int n) {
    vector<string> startTimes(n), endTimes(n);
    for (int i = 0; i < n; ++i) {
        startTimes[i] = "00:00:00";
        endTimes[i] = "23:59:59";
    }
    return startTimes, endTimes;
}