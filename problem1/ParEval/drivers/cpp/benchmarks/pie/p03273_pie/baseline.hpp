#pragma once

#include<vector>
#include<string>
#include<cstring>

std::string baseline(int h, int w, const std::vector<std::string>& grid) {
    std::vector<std::vector<int>> flag(h, std::vector<int>(w, 0));
    std::string result;

    for(int i = 0; i < h; ++i){
        bool p = true;
        for(int j = 0; j < w; ++j){
            if(grid[i][j] != '.') p = false;
        }
        if(p){
            for(int j = 0; j < w; ++j) flag[i][j] = 1;
        }
    }

    for(int j = 0; j < w; ++j){
        bool p = true;
        for(int i = 0; i < h; ++i){
            if(grid[i][j] != '.') p = false;
        }
        if(p){
            for(int i = 0; i < h; ++i) flag[i][j] = 1;
        }
    }

    for(int i = 0; i < h; ++i){
        bool p = false;
        for(int j = 0; j < w; ++j){
            if(!flag[i][j]) { result += grid[i][j]; p = true; }
        }
        if(p) result += '\n';
    }

    return result;
}

std::vector<std::string> generateInput(int h, int w) {
    std::vector<std::string> grid(h, std::string(w, '.'));
    for(int i = 0; i < h; ++i) {
        for(int j = 0; j < w; ++j) {
            if(i % 2 == 0 && j % 2 == 0) grid[i][j] = 'X';
        }
    }
    return grid;
}