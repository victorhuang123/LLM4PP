#pragma once

#include <vector>

int baseline(const std::vector<std::vector<int>>& c) {
    for(int a1 = 0; a1 < 101; a1++)
        for(int a2 = 0; a2 < 101; a2++)
            for(int a3 = 0; a3 < 101; a3++) {
                int b1 = c[0][0] - a1;
                int b2 = c[0][1] - a1;
                int b3 = c[0][2] - a1;

                std::vector<int> a = {a1, a2, a3};
                std::vector<int> b = {b1, b2, b3};

                bool flag = true;
                for(int i = 0; i < 3; i++)
                    for(int j = 0; j < 3; j++)
                        if (a[i] + b[j] != c[i][j])
                            flag = false;

                if (flag) {
                    return 1;
                }
            }

    return 0;
}

std::vector<std::vector<int>> generateExampleInput() {
    return {
        {100, 100, 100},
        {100, 100, 100},
        {100, 100, 100}
    };
}