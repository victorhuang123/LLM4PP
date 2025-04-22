#pragma once

#include <vector>
#include <algorithm>

using namespace std;

long long int baseline(const vector<long long int>& a, const vector<long long int>& m) {
    vector<long long int> p = {1, 1, 1};
    vector<long long int> c = {0, 0, 0};

    for (int i = 0; i < 3; i++) {
        do {
            p[i] = (a[i] * p[i]) % m[i];
            c[i] += 1;
        } while (p[i] != 1);
    }

    long long int gcd = [](long long int a, long long int b) {
        while (b != 0) {
            long long int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    };

    long long int lcm = [](long long int a, long long int b) {
        return a * b / gcd(a, b);
    };

    return lcm(lcm(c[0], c[1]), c[2]);
}

vector<long long int> generateInput() {
    return {999999999999999999LL, 999999999999999999LL, 999999999999999999LL};
}