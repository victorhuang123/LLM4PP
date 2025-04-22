#pragma once

#include<vector>
#include<algorithm>

using namespace std;

long long baseline(int n, const vector<int>& a) {
    vector<int> sum1, sum2;
    long long Sum1 = 0, Sum2 = 0;

    for (int i = 1; i <= n; i += 2)
        if (a[i] > 0) sum1.push_back(i), Sum1 += a[i];
    for (int i = 2; i <= n; i += 2)
        if (a[i] > 0) sum2.push_back(i), Sum2 += a[i];

    vector<int> sum;
    long long Sum;
    if (Sum1 > Sum2) {
        sum = sum1;
        Sum = Sum1;
    } else {
        sum = sum2;
        Sum = Sum2;
    }

    if (Sum == 0) {
        int Max = -1e9 - 7, id;
        for (int i = 1; i <= n; i++)
            if (a[i] > Max) Max = a[i], id = i;
        return Max;
    }

    return Sum;
}

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        a[i] = rand() % 1000000 - 500000;
    }
    return a;
}