#pragma once

#include<vector>
#include<algorithm>
#include<set>
using namespace std;

#define INF (1 << 30)
typedef multiset<int>::iterator itr;

vector<int> generateInput(int N, int Q) {
    vector<int> stmp(N);
    for(int i = 0; i < N; i++) {
        stmp[i] = rand() % 1000000;
    }
    return stmp;
}

int baseline(int N, int Q, vector<int>& stmp, vector<string>& buff, vector<int>& a) {
    vector<int> comp(N);
    for(int i = 0; i < N; i++) {
        comp[i] = stmp[i];
    }
    sort(comp.begin(), comp.end());

    multiset<int> sym;
    int result = 0;
    for(int q = 0; q < Q; q++) {
        if(buff[q][0] == 'A') { //ADD
            sym.insert(stmp[a[q] - 1]);
        } else if(buff[q][0] == 'R') { //REMOVE
            try {
                sym.erase(sym.lower_bound(stmp[a[q] - 1]));
            } catch(...) {}
        } else { //CHECK
            int left = 0, right = INF;
            while(left != right) {
                int center = (left + right) / 2;
                int pre = 0, BAN = 0;
                for(itr it = sym.begin(); it != sym.end(); it++) {
                    int p = distance(comp.begin(), lower_bound(comp.begin(), comp.end(), *it - center));
                    BAN += max(p - pre, 0);
                    pre = distance(comp.begin(), upper_bound(comp.begin(), comp.end(), *it));
                }
                BAN += max(N - pre, 0);
                if(BAN <= a[q]) right = center;
                else left = center + 1;
            }
            if(left != INF) result = left;
            else result = -1;
        }
    }
    return result;
}