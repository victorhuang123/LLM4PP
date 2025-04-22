#pragma once

#include<vector>
#include<algorithm>
using namespace std;

int baseline(int n, vector<int>& model) {
    auto chain = [&](int idx, int col) {
        vector<int> c(n + 1);
        vector<int> f(n, 0);
        for(int i = 0; i < n; i++) {
            if(idx == i)
                c[i] = col;
            else c[i] = model[i];
        }
        c[n] = 100;

        while(true) {
            int flag = 0;
            int curr = c[0], cnt = 1;
            for(int i = 1; i <= n; i++) {
                if(c[i] == 0) continue;
                if(c[i] == curr) cnt++;
                else {
                    curr = c[i];
                    if(cnt >= 4) {
                        flag = 1;
                        for(int j = 0; j < cnt; j++) {
                            if(f[i-1-j] == 1) cnt++;
                            f[i-1-j] = 1;
                            c[i-1-j] = 0;
                        }
                        break;
                    }
                    cnt = 1;
                }
            }
            if(flag == 0) break;
        }

        int cnt = 0;
        for(int i = 0; i < n; i++) {
            if(f[i] == 0) cnt++;
        }
        return cnt;
    };

    int mi = n;
    for(int i = 0; i < n; i++) {
        for(int j = 1; j <= 3; j++) {
            mi = min(mi, chain(i, j));
        }
    }
    return mi;
}

vector<int> generateInput(int n) {
    vector<int> model(n);
    for(int i = 0; i < n; i++) {
        model[i] = rand() % 3 + 1;
    }
    return model;
}