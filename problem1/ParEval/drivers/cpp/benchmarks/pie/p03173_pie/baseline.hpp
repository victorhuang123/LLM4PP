#pragma once

#include <vector>
#include <cstring>
#include <climits>
#include <algorithm>

using namespace std;

#define int long long
#define lop(i,s,e) for(int i=s;i<(int)e;i++)

const int N = 1e3 + 7;
int arr[N], sum[N];
int dp[N][N];

int getsum(int s, int e)
{     
    int sum = 0;
    lop(i,s,e+1) sum += arr[i];
    return sum;
}

int getans(int s, int e)
{     
    if( s >= e ) return 0;
    int &mafia = dp[s][e];
    if( mafia != -1 ) return mafia;

    int ans = LLONG_MAX;

    for(int i = s; i < e; i++)
    {
        int a1 = getans(s,i), a2 = getans(i+1, e);
        int sum1 = getsum(s, i), sum2 = getsum(i+1, e);
        int res = a1 + a2 + sum1 + sum2;
        ans = min(ans, res);
    }

    return mafia = ans;
}

int baseline(int n, const vector<int>& input_arr)
{
    lop(i,1,n+1) arr[i] = input_arr[i-1];
    memset(dp, -1, sizeof dp);
    return getans(1, n);
}

vector<int> generate_input(int n)
{
    vector<int> input_arr(n);
    lop(i,0,n) input_arr[i] = rand() % 1000000 + 1;
    return input_arr;
}