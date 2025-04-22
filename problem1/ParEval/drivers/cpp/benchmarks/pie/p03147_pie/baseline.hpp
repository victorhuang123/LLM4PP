#pragma once

#include <vector>
#include <algorithm>

int baseline(int N) {
    std::vector<std::vector<char>> map(101, std::vector<char>(N + 1, 0));

    int tmp;
    for (int i = 1; i < N + 1; i++) {
        tmp = rand() % 101; // Simulating input with random values
        for (int j = 0; j < 101; j++) {
            if (j < tmp)
                map[j][i] = 1;
            else 
                map[j][i] = 0;
        }
    }

    int count = 0;
    for (int i = 0; i < 101; i++) {
        for (int j = 0; j < N; j++) {
            if (map[i][j] == 0 && map[i][j + 1] == 1) count++;
        }
    }

    return count;
}

std::vector<int> generateInput(int N) {
    std::vector<int> input(N);
    for (int i = 0; i < N; i++) {
        input[i] = rand() % 101;
    }
    return input;
}