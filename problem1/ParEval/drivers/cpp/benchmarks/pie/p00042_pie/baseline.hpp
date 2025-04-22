#pragma once

#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

typedef pair<int, int> P;

int dp[1001][1001];
vector<P> vec;

int rec(int i, int j) {
    if (dp[i][j] >= 0) return dp[i][j];
    int res;
    if (i == vec.size()) res = 0;
    else if (j < vec[i].second) res = rec(i + 1, j);
    else res = max(rec(i + 1, j), rec(i + 1, j - vec[i].second) + vec[i].first);
    return dp[i][j] = res;
}

int baseline(int w, int n, vector<P>& items) {
    memset(dp, -1, sizeof(dp));
    vec = items;
    int max_value = rec(0, w);
    int min_weight = w;
    for (int i = 1; i <= w; i++) {
        if (rec(0, w - i) != max_value) {
            min_weight = w - i + 1;
            break;
        }
    }
    vec.clear();
    return min_weight;
}

vector<P> generate_input(int n, int max_weight, int max_value) {
    vector<P> items(n);
    for (int i = 0; i < n; i++) {
        items[i].first = rand() % max_value + 1;
        items[i].second = rand() % max_weight + 1;
    }
    return items;
}