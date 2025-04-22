#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int a, int b) {
    if(b % a)
        return b - a;
    else
        return a + b;
}

vector<int> generateInput() {
    return {1000000, 1000000000};
}