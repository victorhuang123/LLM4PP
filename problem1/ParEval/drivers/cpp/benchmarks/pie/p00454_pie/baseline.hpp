#pragma once

#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#define F first
#define S second
#define pb push_back
#define rep(i,n) for(int i=0;i<n;i++)
#define all(n) n.begin(),n.end()
using namespace std;

bool used[3010][3010];
static const short dy[] = {0,1,0,-1};
static const short dx[] = {1,0,-1,0};

int baseline(int w, int h, int n, vector<int>& x1, vector<int>& y1, vector<int>& x2, vector<int>& y2) {
    vector<int> x, y;
    for(int i=0; i<n; i++) {
        x.pb(x1[i]); y.pb(y1[i]); x.pb(x2[i]); y.pb(y2[i]);
    }
    x.pb(0); x.pb(w); y.pb(0); y.pb(h);

    sort(all(x)); sort(all(y));
    x.erase(unique(all(x)), x.end()); y.erase(unique(all(y)), y.end());

    int limx = x.size(), limy = y.size();
    rep(i,3010) rep(j,3010) used[i][j] = false;

    rep(i,n) {
        x1[i] = find(all(x), x1[i]) - x.begin();
        y1[i] = find(all(y), y1[i]) - y.begin();
        x2[i] = find(all(x), x2[i]) - x.begin();
        y2[i] = find(all(y), y2[i]) - y.begin();
    }

    int cnt = 0;
    rep(i,limy) rep(j,limx) used[i][j] = i == limy-1 || j == limx-1;

    rep(i,n) for(int k = x1[i]; k < x2[i]; k++) {
        for(int j = y1[i]; j < y2[i]; j++) used[j][k] = true;
    }

    queue<pair<int, int>> que;
    rep(i,limy) {
        rep(j,limx) {
            if(!used[i][j]) {
                que.push({j,i});
                cnt++;
                used[i][j] = true;
                while(!que.empty()) {
                    pair<int, int> p = que.front(); que.pop();
                    rep(k,4) {
                        int nx = p.F + dx[k], ny = p.S + dy[k];
                        if(0 <= nx && nx < limx-1 && 0 <= ny && ny < limy-1 && !used[ny][nx]) {
                            used[ny][nx] = true;
                            que.push({nx,ny});
                        }
                    }
                }
            }
        }
    }
    return cnt;
}

vector<int> generateInput(int n) {
    vector<int> input(n);
    for (int i = 0; i < n; ++i) {
        input[i] = rand() % 3000;
    }
    return input;
}