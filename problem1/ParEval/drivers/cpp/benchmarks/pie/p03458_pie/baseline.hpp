#pragma once

#include<set>
#include<cstdio>
#include<queue>
#include<cmath>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int baseline(int n, int k, const vector<int>& x_coords, const vector<int>& y_coords, const vector<bool>& colors) {
    vector<int> fit(2 * k + 5, 0);
    vector<int> unfit(2 * k + 5, 0);
    int ans = 0;

    for(int x = 0; x <= k; x++) {
        int tmp = 0;
        fill(fit.begin(), fit.end(), 0);
        fill(unfit.begin(), unfit.end(), 0);

        for(int i = 0; i < n; i++) {
            int p = (x <= x_coords[i] && x_coords[i] < x + k);
            int q = (0 <= y_coords[i] && y_coords[i] < k);
            if((p ^ q) == colors[i]) {
                tmp++;
                fit[y_coords[i]]++;
            } else {
                unfit[y_coords[i]]++;
            }
        }

        for(int i = 0; i <= k; i++) {
            if(tmp > ans) ans = tmp;
            if(n - tmp > ans) ans = n - tmp;
            if(i != k)
                tmp = tmp - fit[i] + unfit[i] - fit[i + k] + unfit[i + k];
        }
    }
    return ans;
}

vector<int> generateXCoords(int n, int k) {
    vector<int> x_coords(n);
    for(int i = 0; i < n; i++) {
        x_coords[i] = rand() % (2 * k);
    }
    return x_coords;
}

vector<int> generateYCoords(int n, int k) {
    vector<int> y_coords(n);
    for(int i = 0; i < n; i++) {
        y_coords[i] = rand() % (2 * k);
    }
    return y_coords;
}

vector<bool> generateColors(int n) {
    vector<bool> colors(n);
    for(int i = 0; i < n; i++) {
        colors[i] = rand() % 2;
    }
    return colors;
}