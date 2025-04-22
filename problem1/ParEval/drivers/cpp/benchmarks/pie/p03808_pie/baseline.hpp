#pragma once

#include <vector>
#include <string>

using namespace std;

string baseline(int n, vector<int>& a) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += a[i];
    }

    vector<int> cs(n, 0);
    vector<int> ret(n, 0);
    int cntnum = 0;

    if (sum % (n * (n + 1) / 2)) {
        return "NO";
    } else {
        cntnum = sum / (n * (n + 1) / 2);
        for (int i = 0; i < n; i++) {
            int prev = (i - 1 + n) % n;
            int s = a[prev] - a[i];
            if ((s + cntnum) % n != 0 || (s + cntnum) / n < 0) {
                return "NO";
            }
            cs[i] += (s + cntnum) / n;
        }
        for (int i = 0; i < n; i++) ret[0] += cs[i] * ((n - i) % n + 1);
        for (int i = 1; i < n; i++) ret[i] = ret[i - 1] - cs[i] * n + cntnum;
        for (int i = 0; i < n; i++) {
            if (ret[i] != a[i]) {
                return "NO";
            }
        }
        return "YES";
    }
}

vector<int> generateInput(int n) {
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
    }
    return a;
}