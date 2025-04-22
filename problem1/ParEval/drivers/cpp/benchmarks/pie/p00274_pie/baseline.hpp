#pragma once

#include<vector>
#include<algorithm>

using namespace std;

int baseline(int N, vector<int>& data) {
    bool flag = false;
    for (int i = 0; i < N; i++) {
        if (data[i] > 1) {
            flag = true;
            break;
        }
    }
    if (!flag) {
        return -1;
    } else {
        if (N == 1) {
            return 2;
        } else {
            int ans = 1;
            for (int i = 0; i < N; i++) {
                if (data[i] != 0) ans++;
            }
            return ans;
        }
    }
}

vector<int> generateInput(int N) {
    vector<int> data(N);
    for (int i = 0; i < N; i++) {
        data[i] = (i % 2 == 0) ? i + 2 : 0;
    }
    return data;
}