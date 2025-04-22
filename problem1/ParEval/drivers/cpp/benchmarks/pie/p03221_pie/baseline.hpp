#pragma once

#include <vector>
#include <set>
#include <algorithm>

using namespace std;

struct P {
    int x, y;
};

vector<vector<int>> G;

int POS(int k, int value) {
    int mid;
    int left = 0;
    int len = G[k].size();
    int right = len - 1;

    while (left <= right) {
        mid = left + (right - left) / 2;
        if (G[k][mid] == value) return mid;
        else if (G[k][mid] > value) right = mid;
        else left = mid + 1;
    }
    return -1;
}

vector<int> baseline(int N, int M, vector<P>& H) {
    G.resize(N + 1);
    set<int> s;
    for (int i = 0; i < M; i++) {
        G[H[i].x].push_back(H[i].y);
        s.insert(H[i].x);
    }

    for (int i = 1; i <= N; i++) {
        sort(G[i].begin(), G[i].end());
    }

    vector<int> result;
    for (int i = 0; i < M; i++) {
        result.push_back(POS(H[i].x, H[i].y) + 1);
    }
    return result;
}

vector<P> generateInput(int N, int M) {
    vector<P> H(M);
    for (int i = 0; i < M; i++) {
        H[i].x = rand() % N + 1;
        H[i].y = rand() % 1000000;
    }
    return H;
}