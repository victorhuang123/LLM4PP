#pragma once

#include <bits/stdc++.h>

using namespace std;

vector<int> baseline(int n) {
    vector<int> v;
    int sum = 0;
    vector<int> vis(30002, 0);

    if (n == 3) {
        return {2, 5, 63};
    }

    for (int i = 30000; i >= 2; i -= 2) {
        if (n > 2) {
            v.push_back(i);
            vis[i] = 1;
            n--;
            sum += i;
            if ((i == 8 || i == 6 || i == 4) && n % 2 == 0 && sum % 3 == 0)
                break;
        } else {
            break;
        }
    }

    int j = 3;
    while (n) {
        if (sum % j == 0 && vis[j] == 0) {
            for (int i = j; i < 30000 && n != 0; i += j) {
                if (vis[i] == 0 && i % 2 == 1) {
                    v.push_back(i);
                    vis[i] = 1;
                    n--;
                    sum += i;
                }
            }
        }
        j += 2;
    }

    return v;
}

vector<int> generateInput() {
    return {30000};
}