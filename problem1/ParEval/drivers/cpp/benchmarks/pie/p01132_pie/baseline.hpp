#pragma once

#include <vector>
#include <algorithm>

using namespace std;

int baseline(int N, vector<int> budget) {
    vector<int> coin = { 10, 50, 100, 500 };
    vector<int> used(4, 0);
    int res = 20*20*20*20;

    for (int i=0; i<=budget[0]; i++) {
        int t0 = coin[0]*i;
        for (int j=0; j<=budget[1]; j++) {
            int t1 = coin[1]*j;
            for (int k=0; k<=budget[2]; k++) {
                int t2 = coin[2]*k;
                for (int l=0; l<=budget[3]; l++) {
                    int t3 = coin[3]*l;
                    int charge = (t0+t1+t2+t3) - N;
                    if (charge < 0) continue;
                    int num = 0;
                    for (int m=3; m>=0; m--) {
                        while (charge >= coin[m]) {
                            num++;
                            charge -= coin[m];
                        }
                    }
                    if (res > budget[0]-i+budget[1]-j+budget[2]-k+budget[3]-l+num) {
                        res = budget[0]-i+budget[1]-j+budget[2]-k+budget[3]-l+num;
                        used[0] = i;
                        used[1] = j;
                        used[2] = k;
                        used[3] = l;
                    }
                }
            }
        }
    }

    return res;
}