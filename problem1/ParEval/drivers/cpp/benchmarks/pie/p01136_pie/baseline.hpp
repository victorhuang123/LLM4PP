#pragma once

#include <vector>

using namespace std;

typedef long long STATES;

int baseline(int n, const vector<vector<int>>& free_days_list) {
    STATES goal_state = 0;
    for (int i = 0; i < n; i++) goal_state |= 1LL << i;

    vector<STATES> free_days(30 + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int free_day : free_days_list[i]) {
            free_days[free_day] |= 1LL << i;
        }
    }

    int answer = -1;
    vector<STATES> dp(n, 0);
    for (int i = 0; i < n; i++) dp[i] = 1LL << i;
    for (int i = 1; answer == -1 && i <= 30; i++) {
        STATES next = 0;
        for (int j = 0; j < n; j++) if (free_days[i] & (1LL << j)) next |= dp[j];
        for (int j = 0; j < n; j++) if (free_days[i] & (1LL << j)) dp[j] |= next;
        if (next == goal_state) answer = i;
    }

    return answer;
}

vector<vector<int>> generate_input(int n) {
    vector<vector<int>> free_days_list(n);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= 30; j++) {
            if (rand() % 2) free_days_list[i].push_back(j);
        }
    }
    return free_days_list;
}