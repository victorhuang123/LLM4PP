#pragma once

#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

map<int,int> rot[4] = {
    { {1, 28}, {2, 29}, {3, 30}, {15, 16}, {19, 21}, },
    { {3, 22}, {6, 25}, {9, 28}, {12, 19}, {13, 15} },
    { {7, 22}, {8, 23}, {9, 24}, {13, 18}, {10, 12} },
    { {1, 24}, {4, 27}, {7, 30}, {10, 21}, {16, 18} }
};

vector<int> group_id = {
    0, 0, 0, 0, 0, 0, 0, 0, 0,
    9, 9, 9,
    12, 12, 12,
    15, 15, 15,
    18, 18, 18,
    21, 21, 21, 21, 21, 21, 21, 21, 21
};

void rotate(int i, vector<int>& p) {
    for (auto it=rot[i].begin(); it!=rot[i].end(); ++it) {
        swap(p[it->first - 1], p[it->second - 1]);
    }
}

bool isOK(const vector<int>& p) {
    for (int i=0; i<(int)group_id.size(); ++i) {
        if (p[i] != p[group_id[i]]) return false;
    }
    return true;
}

int solve(int times, int &min_times, vector<int>& p) {
    if (8 <= times || min_times <= times || isOK(p)) {
        min_times = min(min_times, times);
        return times;
    }
    int ret = INT_MAX;
    for (int i=0; i<4; ++i) {
        rotate(i, p);
        ret = min(ret, solve(times + 1, min_times, p));
        rotate(i, p);
    }
    return ret;
}

int baseline(const vector<int>& puzzle) {
    vector<int> p = puzzle;
    int min_times = INT_MAX;
    return solve(0, min_times, p);
}

vector<int> generateInput() {
    vector<int> puzzle(30);
    for (int i = 0; i < 30; ++i) {
        puzzle[i] = i % 9 + 1;
    }
    return puzzle;
}