#pragma once

#include <bits/stdc++.h>

#define ll long long

using namespace std;

ll generateInput() {
    return 81; // Maximum product of two single-digit numbers
}

bool baseline(ll n) {
    for (ll i = 1; i < 10; i++) {
        for (ll j = 1; j < 10; j++) {
            if (i * j == n) {
                return true;
            }
        }
    }
    return false;
}