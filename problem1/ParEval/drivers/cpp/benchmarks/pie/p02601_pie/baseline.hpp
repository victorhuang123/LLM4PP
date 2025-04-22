#pragma once

#include <string>
using namespace std;

string baseline(int a, int b, int c, int k) {
    int cont = 0;
    while(a >= b) {
        cont++;
        b = b * 2;
    }
    while(b >= c) {
        cont++;
        c = c * 2;
    }
    if(cont > k) {
        return "No";
    } else {
        return "Yes";
    }
}