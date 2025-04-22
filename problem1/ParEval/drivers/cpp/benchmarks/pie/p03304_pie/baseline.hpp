#pragma once

#include <vector>
#include <cmath>

using namespace std;

double baseline(lint n, lint m, lint d) {
    return (d ? 2 : 1) * (n - d) * (m - 1) / pow(n, 2);
}

vector<lint> generateInput() {
    return {200000, 200000, 100000};
}