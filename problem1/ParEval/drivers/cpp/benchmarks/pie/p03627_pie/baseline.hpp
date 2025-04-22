#pragma once

#include<vector>
#include<algorithm>
using namespace std;

long long baseline(int n, vector<int>& f) {
    f.resize(n + 1);
    for (int i = 1; i <= n; i++)
        f[i] = i; // Example input generation
    sort(f.begin() + 1, f.end());
    int flag = 0, max1 = 0, max2 = 0;
    for (int i = n - 1; i >= 1; i--)
        if (f[i] == f[i + 1] && !flag) {
            max1 = f[i];
            flag = 1;
        } else if (f[i] == f[i + 1] && flag) {
            if (f[i] == f[i - 1] && f[i] == max1) {
                max2 = f[i];
                break;
            } else if (f[i] != max1) {
                max2 = f[i];
                break;
            }
        }
    return (long long)max1 * (long long)max2;
}