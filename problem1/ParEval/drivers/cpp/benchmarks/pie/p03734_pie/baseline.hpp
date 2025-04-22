#pragma once

#include <bits/stdc++.h>

using namespace std;

int baseline(int N, int W, const vector<int>& weights, const vector<int>& values) {
    map<int, vector<int>> dict;

    for (int i = 1; i <= N; i++) {
        dict[weights[i]].push_back(values[i]);
    }

    for (int i = 0; i <= 3; i++) {
        vector<int>& vect = dict[weights[1] + i];
        sort(vect.begin(), vect.end(), greater<int>());
    }

    int max_value = 0;

    for (int a = 0; (size_t)a <= dict[weights[1]].size(); a++) {
        if (a * weights[1] > W)
            break;

        int value_a = 0;
        for (int i = 0; i < a; i++)
            value_a += dict[weights[1]][i];

        for (int b = 0; (size_t)b <= dict[weights[1] + 1].size(); b++) {
            if (a * weights[1] + b * (weights[1] + 1) > W)
                break;

            int value_b = 0;
            for (int i = 0; i < b; i++)
                value_b += dict[weights[1] + 1][i];

            for (int c = 0; (size_t)c <= dict[weights[1] + 2].size(); c++) {
                if (a * weights[1] + b * (weights[1] + 1) + c * (weights[1] + 2) > W)
                    break;

                int value_c = 0;
                for (int i = 0; i < c; i++)
                    value_c += dict[weights[1] + 2][i];

                for (int d = 0; (size_t)d <= dict[weights[1] + 3].size(); d++) {
                    if (a * weights[1] + b * (weights[1] + 1) + c * (weights[1] + 2) + d * (weights[1] + 3) > W)
                        break;

                    int value_d = 0;
                    for (int i = 0; i < d; i++)
                        value_d += dict[weights[1] + 3][i];

                    max_value = max(max_value, value_a + value_b + value_c + value_d);
                }
            }
        }
    }

    return max_value;
}

vector<int> generateWeights(int N) {
    vector<int> weights(N + 1);
    for (int i = 1; i <= N; i++) {
        weights[i] = rand() % 100 + 1;
    }
    return weights;
}

vector<int> generateValues(int N) {
    vector<int> values(N + 1);
    for (int i = 1; i <= N; i++) {
        values[i] = rand() % 1000 + 1;
    }
    return values;
}