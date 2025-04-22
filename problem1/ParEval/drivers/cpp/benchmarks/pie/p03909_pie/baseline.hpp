
#include <bits/stdc++.h>
using namespace std;

string baseline(int h, int w, vector<vector<string>>& grid) {
    string f = "snuke";
    int x = 0, y = 0;
    for(int i = 1; i <= h; ++i) {
        for(int j = 1; j <= w; ++j) {
            if(grid[i][j] == f) {
                x = i;
                y = j;
            }
        }
    }
    char z = 'A' + y - 1;
    return string(1, z) + to_string(x);
}