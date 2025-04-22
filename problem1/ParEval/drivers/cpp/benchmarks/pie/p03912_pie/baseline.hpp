#pragma once

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define fbo find_by_order
#define ook order_of_key

typedef long long ll;
typedef pair<ll,ll> ii;
typedef vector<int> vi;
typedef long double ld; 
typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> pbds;
typedef set<int>::iterator sit;
typedef map<int,int>::iterator mit;
typedef vector<int>::iterator vit;

int baseline(int n, int m, const vector<int>& input) {
    map<int,int> cnt[100001];
    vi vec[100001];

    for(int i=0;i<n;i++) {
        int x = input[i];
        cnt[x%m][x]++;
    }

    for(int i = 0; i < m; i++) {
        for(mit it = cnt[i].begin(); it != cnt[i].end(); it++) {
            vec[i].pb(it->se);
        }
    }

    int ans = 0;
    for(int i = 0; 2*i <= m; i++) {
        if(i==0||i==m-i) {
            int sum=0;
            for(int j = 0; j < vec[i].size(); j++) {
                sum+=vec[i][j];
            }
            ans+=sum/2;
        } else {
            int clr1 = 0;
            int clr2 = 0;
            int sum1 = 0;
            int sum2 = 0;
            for(int j = 0; j < vec[i].size(); j++) {
                sum1 += vec[i][j];
                clr1 += (vec[i][j]/2);
            }
            for(int j = 0; j < vec[m-i].size(); j++) {
                sum2 += vec[m-i][j];
                clr2 += (vec[m-i][j]/2);
            }
            if(sum1>=sum2) {
                int mindel = min(clr1, (sum1-sum2)/2);
                sum1 -= 2*mindel;
                ans += min(sum1,sum2) + mindel;
            } else {
                int mindel = min(clr2, (sum2-sum1)/2);
                sum2 -= 2*mindel;
                ans += min(sum1,sum2) + mindel;
            }
        }
    }
    return ans;
}

vector<int> generateInput(int n) {
    vector<int> input(n);
    for(int i = 0; i < n; i++) {
        input[i] = rand() % 100000 + 1;
    }
    return input;
}