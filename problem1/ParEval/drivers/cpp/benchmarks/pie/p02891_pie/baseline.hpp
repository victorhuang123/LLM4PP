#pragma once

#include <string>
using namespace std;

long long baseline(string T, long long K) {
    bool flag = true;
    for (int i = 0; i < (int)T.size() - 1; i++) {
        if (T[i] != T[i + 1]) flag = false;
    }

    if (flag == true) {
        long long len = 1LL * (long long)(T.size()) * K;
        return len / 2LL;
    } else {
        long long cnt = 0, ret1 = 0, ret2 = 0;
        for (int i = 0; i < T.size(); i++) {
            cnt++;
            if (i == (int)T.size() - 1 || T[i] != T[i + 1]) {
                ret1 += cnt / 2;
                cnt = 0;
            }
        }
        cnt = 0;
        string V2 = T + T;
        for (int i = 0; i < V2.size(); i++) {
            cnt++;
            if (i == (int)V2.size() - 1 || V2[i] != V2[i + 1]) {
                ret2 += cnt / 2;
                cnt = 0;
            }
        }
        return ret1 + (ret2 - ret1) * (K - 1LL);
    }
}

string generateInput() {
    return "aabbbbaabbbbaabbbbaabbbbaabbbbaabbbbaabbbbaabbbbaabbbbaabbbb";
}