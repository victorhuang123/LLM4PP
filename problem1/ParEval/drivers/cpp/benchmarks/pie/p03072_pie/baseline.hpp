#pragma once

#include<bits/stdc++.h>

using namespace std;

int baseline(int n, const vector<int>& arreglo) {
    int cont = 0;

    for(int i = 0; i < n; i++) {
        bool cuenta = true;

        for(int j = 0; j < i; j++) {
            if(arreglo[j] > arreglo[i]) {
                cuenta = false;
                break;
            }
        }

        if(cuenta) cont++;
    }

    return cont;
}

vector<int> generateInput(int n) {
    vector<int> arreglo(n);
    for(int i = 0; i < n; i++) {
        arreglo[i] = rand() % 1000000;
    }
    return arreglo;
}