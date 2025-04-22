#pragma once

#include<vector>
#include<string>
#define ll long long

vector<string> baseline(int T, ll a, ll b, ll c, ll d) {
    vector<string> results;
    bool tag;
    ll now, x, y;

    while (T--) {
        if (a < b) {
            results.push_back("No");
            continue;
        }
        now = a; tag = 1;
        if (b > d) {
            results.push_back("No");
            continue;
        }
        if (b <= c) {
            results.push_back("Yes");
            continue;
        }
        if (b == d) {
            if (now % b > c) results.push_back("No");
            else results.push_back("Yes");
            continue;
        }
        now = now % b;
        x = d % b;
        if (now > c) {
            results.push_back("No");
            continue;
        }
        if (x == 0) {
            results.push_back("Yes");
            continue;
        }
        if (c == b - 1) {
            results.push_back("Yes");
            continue;
        }
        for (int i = 1; i <= 100000; i++) {
            y = (b - 1 - now) / x;
            now = now + x * y;
            if (now > c) {
                tag = 0;
                break;
            }
            now = (now + x) % b;
        }
        if (tag) results.push_back("Yes");
        else results.push_back("No");
    }
    return results;
}