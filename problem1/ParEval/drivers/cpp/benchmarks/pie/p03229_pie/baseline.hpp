#pragma once

#include <bits/stdc++.h>

using namespace std;

typedef long long llt;

llt baseline(const vector<llt>& A) {
    int N = A.size();
    llt ans1 = 0, ans2 = 0;
    deque<llt> que1, que2;

    vector<llt> sortedA = A;
    sort(sortedA.begin(), sortedA.end());

    que1.push_back(sortedA[0]);
    que2.push_back(sortedA[N - 1]);

    llt Max = sortedA[N - 1], Min = sortedA[1];
    int Maxi = N - 1, Mini = 1;
    for (int i = 1; i < N; ++i) {
        llt F = que1.front(), L = que1.back();
        llt ValF = max(abs(F - Max), abs(F - Min)),
            ValL = max(abs(L - Max), abs(L - Min));
        if (ValF > ValL) {
            ans1 += ValF;
            if (abs(F - Max) == ValF) que1.push_front(Max), Maxi--;
            else que1.push_front(Min), Mini++;
        } else {
            ans1 += ValL;
            if (abs(L - Max) == ValL) que1.push_back(Max), Maxi--;
            else que1.push_back(Min), Mini++;
        }
        Max = sortedA[Maxi]; Min = sortedA[Mini];
    }

    Max = sortedA[N - 2], Min = sortedA[0];
    Maxi = N - 2, Mini = 0;
    for (int i = 1; i < N; ++i) {
        llt F = que2.front(), L = que2.back();
        llt ValF = max(abs(F - Max), abs(F - Min)),
            ValL = max(abs(L - Max), abs(L - Min));
        if (ValF > ValL) {
            ans2 += ValF;
            if (abs(F - Max) == ValF) que2.push_front(Max), Maxi--;
            else que2.push_front(Min), Mini++;
        } else {
            ans2 += ValL;
            if (abs(L - Max) == ValL) que2.push_back(Max), Maxi--;
            else que2.push_back(Min), Mini++;
        }
        Max = sortedA[Maxi]; Min = sortedA[Mini];
    }

    return max(ans1, ans2);
}

vector<llt> generateInput(int N) {
    vector<llt> A(N);
    for (int i = 0; i < N; ++i) {
        A[i] = rand() % 1000000000 + 1;
    }
    return A;
}