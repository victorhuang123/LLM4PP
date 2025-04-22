#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int n, int m) {
    vector<vector<int>> memo(3, vector<int>(m + 1, -1));
    for(int i = 0; i < 3; i++) memo[i][0] = 0;

    int ans = 0;
    for(int i = 0; i < n; i++) {
        int cost, prm[3];
        cost = rand() % 100 + 1;
        prm[0] = rand() % 100 + 1;
        prm[1] = rand() % 100 + 1;
        prm[2] = rand() % 100 + 1;

        for(int j = 0; j < 3; j++) {
            for(int k = 0; k + cost <= m; k++) {
                if(memo[j][k] == -1) continue;
                memo[j][k + cost] = max(memo[j][k + cost], memo[j][k] + prm[j]);
                ans = max(ans, memo[j][k + cost]);
            }
        }
    }
    return ans;
}

vector<int> generateInput(int n, int m) {
    vector<int> input;
    input.push_back(n);
    input.push_back(m);
    for(int i = 0; i < n; i++) {
        input.push_back(rand() % 100 + 1); // cost
        input.push_back(rand() % 100 + 1); // profit1
        input.push_back(rand() % 100 + 1); // profit2
        input.push_back(rand() % 100 + 1); // profit3
    }
    return input;
}