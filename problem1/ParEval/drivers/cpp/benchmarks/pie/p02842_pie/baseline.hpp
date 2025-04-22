#pragma once

#include <vector>

using namespace std;

vector<int> generateInput() {
    vector<int> input;
    for (int i = 1; i <= 50000; ++i) {
        input.push_back(i);
    }
    return input;
}

int baseline(int N) {
    vector<int> exist = generateInput();

    for (int i = 0; i < exist.size(); ++i) {
        if ((int)((float)exist[i] * 1.08) == N) {
            return exist[i];
        }
    }
    return -1;
}