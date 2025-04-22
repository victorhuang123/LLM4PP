#pragma once

#include <bits/stdc++.h>

using namespace std;

#define all(v) v.begin(), v.end()

#define repi(i,n) for(int i=0;i<(int)(n);i++)

#define repd(i,n) for(int i=(int)(n);i>=0;i--)

#define repm(i,m) for(auto i=m.begin();i!=m.end();i++)

double baseline(int N, vector<int>& X, vector<int>& Y) {
    vector<int> path(N);
    repi(i,N){
        path[i] = i;
    }

    double sum = 0.0;
    do{
        repi(i,N-1){
            int dx = X.at(path.at(i)) - X.at(path.at(i+1));
            int dy = Y.at(path.at(i)) - Y.at(path.at(i+1));
            sum += pow(dx*dx + dy*dy, 0.5);
        }
    } while (next_permutation(all(path)));

    int Frac = 1;
    for(int i=2;i <= N;i++){
        Frac *= i;
    }
    return sum / Frac;
}

vector<int> generateInput(int N) {
    vector<int> X(N), Y(N);
    repi(i, N) {
        X[i] = rand() % 1000;
        Y[i] = rand() % 1000;
    }
    return {X, Y};
}