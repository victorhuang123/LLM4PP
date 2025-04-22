#pragma once

#include<bits/stdc++.h>

#define mk make_pair

#define r(i,n) for(int i=0;i<n;i++)

using namespace std;

int baseline(int h, int w, vector<string>& s) {
    int sum = 0;
    vector<int> x, y;

    r(i, h) r(j, w) if(s[i][j] != '.') {
        y.push_back(i), x.push_back(j);
        if(i+1 < h) y.push_back(i+1);
        if(j+1 < w) x.push_back(j+1);
    }

    auto del = [&](int t1, int t2) {
        vector<pair<char, pair<int, int>>> p;

        for(int i = t1; i < h; i++) if(s[i][t2] != '.') {
            p.push_back(mk(s[i][t2], mk(i, t2)));
            break;
        }

        for(int i = t1; i >= 0; i--) if(s[i][t2] != '.') {
            p.push_back(mk(s[i][t2], mk(i, t2)));
            break;
        }

        for(int i = t2; i < w; i++) if(s[t1][i] != '.') {
            p.push_back(mk(s[t1][i], mk(t1, i)));
            break;
        }

        for(int i = t2; i >= 0; i--) if(s[t1][i] != '.') {
            p.push_back(mk(s[t1][i], mk(t1, i)));
            break;
        }

        sort(p.begin(), p.end());

        if(p.size() >= 2) {
            r(i, p.size() - 1) {
                if(p[i].first == p[i+1].first) {
                    sum++;
                    s[p[i].second.first][p[i].second.second] = '.';
                    s[p[i+1].second.first][p[i+1].second.second] = '.';
                }
            }
        }
    };

    r(k, 26) r(i, y.size()) r(j, x.size())
        if(s[y[i]][x[j]] == '.') del(y[i], x[j]);

    return sum * 2;
}

vector<string> generateInput(int h, int w) {
    vector<string> s(h, string(w, '.'));
    r(i, h) r(j, w) if(rand() % 2) s[i][j] = 'A' + rand() % 26;
    return s;
}