#pragma once

#include <vector>
#include <algorithm>

using namespace std;

typedef vector<int> V;

int baseline(V s, int q, V targets) {
    int c = 0;
    for (int i = 0; i < q; i++) {
        int t = targets[i];
        int left = 0;
        int right = s.size();
        while (left < right) {
            int mid = (left + right) / 2;
            if (s[mid] == t) {
                c++;
                break;
            } else if (s[mid] > t) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
    }
    return c;
}

V generate_input() {
    V s(1000000);
    for (int i = 0; i < 1000000; i++) {
        s[i] = i * 2;
    }
    V targets(100000);
    for (int i = 0; i < 100000; i++) {
        targets[i] = i * 2 + 1;
    }
    return s, targets;
}