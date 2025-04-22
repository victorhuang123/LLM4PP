#pragma once

#include <bits/stdc++.h>

#define PB push_back
#define MP make_pair
#define REP(i,n) for (int i=0;i<(n);i++)
#define FOR(i,a,b) for(int i=(a);i<(b);i++)
#define ALL(a) (a).begin(),(a).end()

using namespace std;

typedef pair<int,int> P;
typedef long long ll;
const int INF=1e9;

int baseline(int m, int n, vector<int>& p, vector<int>& c, vector<int>& e) {
    vector<int> dp(100100, INF);
    dp[0] = 0;
    int sum = 0;

    REP(i,n) {
        for(int j=sum;j>=0;j--) {
            dp[j+c[i]] = min(dp[j+c[i]], dp[j] + e[i]);
        }
        sum += c[i];
        sum = min(sum, 20000);
    }

    for(int i=sum;i>=0;i--) {
        dp[i] = min(dp[i], dp[i+1]);
    }

    sort(ALL(p), greater<int>());
    sum = 0;
    int ans = 0;

    REP(i,m) {
        sum += p[i];
        ans = max(ans, sum - dp[i+1]);
    }

    return ans;
}

vector<int> generateInput(int m, int n) {
    vector<int> p(m), c(n), e(n);
    REP(i, m) p[i] = rand() % 1000 + 1;
    REP(i, n) c[i] = rand() % 100 + 1;
    REP(i, n) e[i] = rand() % 100 + 1;
    return {m, n, p, c, e};
}