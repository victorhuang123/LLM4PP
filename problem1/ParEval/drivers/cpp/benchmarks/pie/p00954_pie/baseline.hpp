#pragma once

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int ExGCD(int a, int b, int &x, int &y){
    int d=a;
    x=1; y=0;
    if(b!=0){ d=ExGCD(b, a%b, y, x); y-=a/b*x; }
    return d;
}

string baseline(int n, const vector<int>& a_values, const vector<int>& b_values){
    string result;
    for(int i=0; i<n; i++){
        int a = a_values[i];
        int b = b_values[i];
        int x, y, d;
        d = ExGCD(a, b, x, y);
        if(d <= 50000){
            result += "3\n0 0\n" + to_string(a) + " " + to_string(b) + "\n" + to_string(abs(y)) + " " + to_string(abs(x)) + "\n";
        }else{
            result += "4\n0 0\n" + to_string(a-1) + " " + to_string(b) + "\n" + to_string(a/d) + " " + to_string(b/d) + "\n" + to_string(a) + " " + to_string(b-1) + "\n";
        }
    }
    return result;
}

vector<int> generateInput(int n){
    vector<int> a_values(n, 1000000007);
    vector<int> b_values(n, 1000000009);
    return a_values, b_values;
}