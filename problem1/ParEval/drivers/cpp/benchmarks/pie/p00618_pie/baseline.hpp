#pragma once

#include<vector>
#include<queue>
#include<cstring>

using namespace std;

int baseline(int N, int U, vector<int>& unit, vector<int>& need) {
    vector<bool> visited(1 << 20, false);
    queue<State> up;
    State s;
    s.one = 0;
    s.mask = 0;
    s.have = 0;
    visited[s.mask] = true;
    up.push(s);
    while(!up.empty()) {
        s = up.front(); up.pop();
        if(s.have >= U) return s.one;
        for(int i = 0; i < N; i++) {
            if(!visited[s.mask | (1 << i)] && (s.mask | need[i]) == s.mask) {
                State next;
                next.mask = s.mask | (1 << i);
                next.one = s.one + 1;
                next.have = s.have + unit[i];
                visited[next.mask] = true;
                up.push(next);
            }
        }
    }
    return -1;
}

vector<int> generateInput(int N, int U) {
    vector<int> unit(N);
    vector<int> need(N);
    for(int i = 0; i < N; i++) {
        unit[i] = (i + 1) * 50000;
        need[i] = (1 << i) - 1;
    }
    return {unit, need};
}