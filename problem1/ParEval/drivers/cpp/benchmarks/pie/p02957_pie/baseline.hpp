#pragma once

#include<bits/stdc++.h>

using namespace std;

vector<int> generate_input() {
    vector<int> input = {1000000000, 1000000000};
    return input;
}

int baseline(int a, int b) {
    if(a == b) {
        return 1;
    } else if((a + b) % 2 == 0) {
        return (a + b) / 2;
    } else {
        return -1; // Using -1 to represent "IMPOSSIBLE"
    }
}