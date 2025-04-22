#pragma once

#include<vector>
using namespace std;

bool baseline(int h, int w, vector<vector<char>>& a) {
    vector<int> fir(h + 1, 0), las(h + 1, 0);
    bool ans = true;

    for(int i = 1; i <= h; i++) {
        int num = 0;
        for(int j = 1; j <= w; j++) {
            if(a[i][j] == '#' && (j == w || a[i][j+1] != '#'))
                num++, las[i] = j;
            if(!fir[i] && a[i][j] == '#')
                fir[i] = j;
        }
        if(num != 1) ans = false;
        if(i > 1 && fir[i] != las[i-1]) ans = false;
    }
    if(a[h][w] != '#') ans = false;
    return ans;
}

vector<vector<char>> generateInput(int h, int w) {
    vector<vector<char>> a(h + 1, vector<char>(w + 1, '.'));
    for(int i = 1; i <= h; i++) {
        for(int j = 1; j <= w; j++) {
            if(i == j || i == j + 1) a[i][j] = '#';
        }
    }
    return a;
}