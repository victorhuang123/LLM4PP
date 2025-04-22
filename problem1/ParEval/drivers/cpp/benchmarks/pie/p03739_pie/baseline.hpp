#pragma once

#include <bits/stdc++.h>
using namespace std;

long baseline(long n, const vector<long>& arr) {
    long contA = 0, contB = 0, sumB = 0, sumA = 0;

    if(arr[0] < 0){
        contB += abs(arr[0]) + 1;
        sumB = 1;     
        sumA = arr[0];       
    }else if(arr[0] > 0){
        contA += abs(arr[0]) + 1;
        sumA = -1;
        sumB = arr[0];     
    }
    if(arr[0] == 0){
        contB++;
        contA++;
        sumA = -1;
        sumB = 1;
    }

    for(int i = 1; i < n; i++){
        if(sumA > 0){
            sumA += arr[i];
            if(sumA >= 0){
                contA += sumA + 1;
                sumA = -1;
            }
        }else if(sumA < 0){
            sumA += arr[i];
            if(sumA <= 0){
                contA += abs(sumA) + 1;
                sumA = 1;                            
            }
        }

        if(sumB > 0){
            sumB += arr[i];
            if(sumB >= 0){
                contB += sumB + 1;
                sumB = -1;
            }
        }else if(sumB < 0){
            sumB += arr[i];
            if(sumB <= 0){
                contB += abs(sumB) + 1;
                sumB = 1;
            }
        }
    }

    return min(contA, contB);
}

vector<long> generateInput(long n) {
    vector<long> arr(n);
    for(long i = 0; i < n; i++) {
        arr[i] = (i % 2 == 0) ? -1 : 1;
    }
    return arr;
}