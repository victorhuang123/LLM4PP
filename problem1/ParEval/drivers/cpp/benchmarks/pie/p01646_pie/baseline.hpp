#pragma once

#include<bits/stdc++.h>

using namespace std;

bool baseline(int n, vector<string>& str) {
    vector<vector<int>> vis(255, vector<int>(255, 0));
    vector<int> in(255, 0);
    for(int i = 1; i < n; i++) {
        for(int j = 0; j < str[i].size() || j < str[i-1].size(); j++) {
            if(j >= str[i].size() || j >= str[i-1].size()) {
                if(j >= str[i].size()) return false;
                break;
            }
            if(str[i][j] == str[i-1][j]) continue;
            int x = (int)(str[i-1][j]);
            int y = (int)(str[i][j]);
            if(vis[y][x]) return false;
            if(!vis[x][y]) {
                vis[x][y] = 1;
                in[y]++;
            }
            break;
        }
    }
    queue<int> q;
    for(int i = 0; i < 255; i++) if(in[i] == 0) q.push(i);
    int num = 0;
    while(!q.empty()) {
        int u = q.front(); q.pop(); num++;
        for(int i = 0; i < 255; i++) {
            if(vis[u][i]) {
                in[i]--;
                if(in[i] == 0) q.push(i);
            }
        }
    }
    return num == 255;
}

vector<string> generateInput() {
    vector<string> str(555);
    for(int i = 0; i < 555; i++) {
        str[i] = string(22, 'a' + (i % 26));
    }
    return str;
}