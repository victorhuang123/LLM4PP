#pragma once

#include <bits/stdc++.h>

using namespace std;

const long long N = 1e6+5 , M = 998244353, OO = 0x3f3f3f3f;

typedef long long ll;

#define FIO ios_base::sync_with_stdio(0);cin.tie(0);

const double Pii = 3.14159265359;

int cr[] = {-1, 1, 0, 0};
int cc[] = {0, 0, -1, 1};

bool valid(int nr, int nc, int n, int m) {
    return (nr >= 0 && nr < n && nc >= 0 && nc < m);
}

int baseline(int n, int m, int mxk, int X1, int Y1, int X2, int Y2, vector<bool>& grid) {
    vector<int> dis(N, OO);
    dis[X1*m+Y1] = 0;
    queue<pair<int, int>> q;
    q.push({X1, Y1});
    while(!q.empty()) {
        pair<int, int> pu = q.front();
        q.pop();
        for(int k=0; k<4; ++k) {
            int kused = 0;
            bool ok = 1;
            int nr = pu.first;
            int nc = pu.second;
            while(kused < mxk && ok) {
                nr += cr[k];
                nc += cc[k];
                if(valid(nr, nc, n, m) && grid[nr*m+nc] && dis[nr*m+nc] >= dis[pu.first*m+pu.second]+1) {
                    if(dis[nr*m+nc] > dis[pu.first*m+pu.second] + 1) {
                        q.push({nr, nc});
                        dis[nr*m+nc] = dis[pu.first*m+pu.second] + 1;
                    }
                    kused++;
                }
                else ok = 0;
            }
        }
    }
    return dis[X2*m+Y2];
}

vector<bool> generateInput(int n, int m) {
    vector<bool> grid(n * m, true);
    return grid;
}