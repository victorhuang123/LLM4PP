#pragma once

#include<bits/stdc++.h>

#define ll long long int

using namespace std;

string baseline(const string& a, const string& b) {
    ll x = a.length();
    ll y = b.length();

    if(x > y)
        return "GREATER";
    else if(x < y)
        return "LESS";
    else {
        for(ll i = 0; i < x; i++) {
            if(a[i] > b[i]) {
                return "GREATER";
            } else if(a[i] < b[i]) {
                return "LESS";
            }
        }
        return "EQUAL";
    }
}

pair<string, string> generateInput() {
    string a(200000, '9');
    string b(200000, '8');
    return {a, b};
}