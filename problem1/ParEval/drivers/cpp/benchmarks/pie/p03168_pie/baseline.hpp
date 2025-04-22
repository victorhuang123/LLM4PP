#pragma once

#include<bits/stdc++.h>

using namespace std;

#define ll long long
#define MAX 3100

double dp[MAX][MAX];
bool visited[MAX][MAX];

double calc(ll pos, ll nisi, ll n, ll req, const vector<double>& v) {
    if (pos >= n) {
        if (nisi >= req) return 1.0;
        else return 0.0;
    } else if (dp[pos][nisi] > -1.0) return dp[pos][nisi];

    double r1 = 0.00, r2 = 0.0;
    double head = v[pos];
    double tail = 1.00 - v[pos];

    r1 += (calc(pos + 1, nisi + 1, n, req, v) * head);
    r2 += (calc(pos + 1, nisi, n, req, v) * tail);

    return dp[pos][nisi] = r1 + r2;
}

double baseline(ll n, const vector<double>& probabilities) {
    ll req = (n + 2) / 2;

    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < n; j++) {
            dp[i][j] = -1.0;
        }
    }

    memset(visited, false, sizeof visited);

    return calc(0, 0, n, req, probabilities);
}

vector<double> generateInput() {
    vector<double> probabilities(MAX);
    for (int i = 0; i < MAX; ++i) {
        probabilities[i] = 0.5; // Example input with maximum scale
    }
    return probabilities;
}