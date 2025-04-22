#pragma once

#include <vector>
#include <algorithm>

using namespace std;

long long int baseline(long long int num1, long long int num2) {
    long long int gcd, res, lcm;
    res = num1 * num2;
    while(num1 != num2) {
        if(num1 > num2)
            num1 = num1 - num2;
        else
            num2 = num2 - num1;
    }
    gcd = num1;
    lcm = res / gcd;
    return lcm;
}

vector<long long int> generateInput() {
    vector<long long int> input = {999999999999999999LL, 999999999999999998LL};
    return input;
}