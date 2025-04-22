#pragma once

#include<vector>

using namespace std;

vector<vector<int>> baseline(int n) {
    vector<vector<vector<int>>> kek(n + 1);

    for(int i = 1; i <= n; i++) {
        vector<int> hn;
        hn.push_back(i);
        kek[i].push_back(hn);

        for(int j = i - 1; j > 0; j--) {
            for(int k = 0; k < kek[i - j].size(); k++) {
                int flg = 0;

                for(int p = 0; p < kek[i - j][k].size(); p++) {
                    if(kek[i - j][k][p] > j) {
                        flg = 1;
                        break;
                    }
                }

                if(flg == 1) {
                    continue;
                }

                vector<int> u;
                u.push_back(j);

                for(int p = 0; p < kek[i - j][k].size(); p++) {
                    u.push_back(kek[i - j][k][p]);
                }
                kek[i].push_back(u);
            }
        }
    }

    return kek[n];
}

vector<int> generateInput() {
    return {30};
}