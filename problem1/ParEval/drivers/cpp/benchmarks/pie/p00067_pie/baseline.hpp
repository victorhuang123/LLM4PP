#pragma once

#include<vector>

using namespace std;

int baseline(vector<vector<int>>& masu) {
    int cont = 0;
    int rows = masu.size();
    int cols = masu[0].size();

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (masu[i][j] == 1) {
                cont++;
                deque<pair<int, int>> stack;
                stack.push_back({i, j});
                masu[i][j] = 0;

                while (!stack.empty()) {
                    auto [x, y] = stack.back();
                    stack.pop_back();

                    if (x + 1 < rows && masu[x + 1][y] == 1) {
                        masu[x + 1][y] = 0;
                        stack.push_back({x + 1, y});
                    }
                    if (y + 1 < cols && masu[x][y + 1] == 1) {
                        masu[x][y + 1] = 0;
                        stack.push_back({x, y + 1});
                    }
                    if (x - 1 >= 0 && masu[x - 1][y] == 1) {
                        masu[x - 1][y] = 0;
                        stack.push_back({x - 1, y});
                    }
                    if (y - 1 >= 0 && masu[x][y - 1] == 1) {
                        masu[x][y - 1] = 0;
                        stack.push_back({x, y - 1});
                    }
                }
            }
        }
    }

    return cont;
}

vector<vector<int>> generateInput() {
    int size = 1000;
    vector<vector<int>> masu(size, vector<int>(size, 1));
    return masu;
}