#pragma once

#include<vector>
#include<queue>
#include<cstring>
using namespace std;

#define fr first
#define sc second
typedef pair<int,int> Pt;
typedef pair<Pt ,int> P;

int baseline(int h, int w, vector<vector<char>>& grid) {
    Pt ST;
    int c = 0;
    for(int i=0;i<h;i++){
        for(int j=0;j<w;j++){
            if(grid[i][j] == 'o') ST = Pt(i,j);
            else if(grid[i][j] == '*') grid[i][j] = c++;
        }
    }

    int used[20][20][1 << 10];
    memset(used,-1,sizeof(used));
    queue<P> que;
    que.push(P(ST,0));
    used[ST.fr][ST.sc][0] = 0;
    int d[]={0,1,0,-1};

    while(!que.empty()){
        P p = que.front();
        que.pop();
        if(p.sc==(1<<c)-1) return used[p.fr.fr][p.fr.sc][p.sc];
        int log = used[p.fr.fr][p.fr.sc][p.sc];
        for(int i=0;i<4;i++){
            int nx = d[i] + p.fr.fr, ny = d[3-i] + p.fr.sc;
            int bits = p.sc;
            if(nx>=0&&nx<h&&ny>=0&&ny<w){
                if(grid[nx][ny] == 'x') continue;
                if(grid[nx][ny] >= 0 && grid[nx][ny] < 10){
                    bits |= 1<<grid[nx][ny];
                }
                if(used[nx][ny][bits] != -1) continue;
                que.push(P(Pt(nx,ny),bits));
                used[nx][ny][bits] = log + 1;
            }
        }
    }
    return -1;
}

vector<vector<char>> generateInput(int h, int w) {
    vector<vector<char>> grid(h, vector<char>(w, '.'));
    grid[0][0] = 'o';
    for(int i = 0; i < h; i++) {
        for(int j = 0; j < w; j++) {
            if(grid[i][j] != 'o' && (i + j) % 5 == 0) {
                grid[i][j] = '*';
            }
        }
    }
    return grid;
}