#pragma once

#include<vector>
#include<sstream>
#include<cmath>
#include<algorithm>

using namespace std;

const int MAX = 13;

double baseline(double box, const string& input) {
    vector<double> Cake;
    double dp[(1<<MAX)][MAX];
    fill(dp[0], dp[0] + (1<<MAX) * MAX, 100000000);
    dp[0][0] = 0;

    stringstream ss(input);
    double num;
    while (ss >> num) Cake.push_back(num);

    for (int i = 0; i < (1 << Cake.size()); i++) {
        for (int j = 0; j < (int)Cake.size(); j++) {
            if (i == 0) {
                dp[(1 << j)][j] = Cake[j];
                continue;
            }
            for (int k = 0; k < (int)Cake.size(); k++) {
                if (!(i & (1 << k)) && j != k) {
                    dp[i + (1 << k)][k] = min(dp[i + (1 << k)][k], dp[i][j] + 2.0 * sqrt(Cake[j] * Cake[k]));
                }
            }
        }
    }

    for (int i = 0; i < (int)Cake.size(); i++) {
        if (dp[(1 << Cake.size()) - 1][i] + Cake[i] <= box) {
            return 1; // OK
        }
    }
    return 0; // NA
}

vector<double> generateInput() {
    vector<double> input;
    for (int i = 1; i <= MAX; ++i) {
        input.push_back(i * 1.0);
    }
    return input;
}