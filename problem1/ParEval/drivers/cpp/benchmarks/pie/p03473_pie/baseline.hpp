#pragma once

#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>
#include<stack>
#include<set>
#include<map>
using namespace std;

typedef long long ll;
const int mod = 1000000007;
const int INF = 1001001001;

int baseline(int m) {
    return 48 - m;
}

vector<int> generate_input() {
    vector<int> input;
    for (int i = 0; i < 1000000; ++i) {
        input.push_back(i % 100);
    }
    return input;
}