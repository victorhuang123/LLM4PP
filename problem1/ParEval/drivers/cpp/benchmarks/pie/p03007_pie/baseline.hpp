#pragma once

#include <bits/stdc++.h>

#define ll long long 
#define maxn 500005
#define INF 0x3f3f3f3f

using namespace std;

struct Node {
    int x, y;
    Node():x(0), y(0){}
    Node(int xx, int yy): x(xx), y(yy){}
};

vector<Node> baseline(int n, vector<int>& a) {
    vector<Node> ans;
    vector<bool> vis(n + 1, false);
    int da = 0, xiao = 0;

    for(int i = 1; i <= n; i++) {
        if(a[i] >= 0) da++;
        else xiao++;
    }

    if(!xiao) {
        sort(a.begin() + 1, a.end());
        int p = a[1];
        for(int i = 2; i <= n - 1; i++) {
            ans.push_back(Node(p, a[i]));
            p -= a[i];
        }
        ans.push_back(Node(a[n], p));
    } else if(!da) {
        sort(a.begin() + 1, a.end());
        int p = a[n];
        for(int i = n - 1; i >= 2; i--) {
            ans.push_back(Node(p, a[i]));
            p -= a[i];
        }
        ans.push_back(Node(p, a[1]));
    } else {
        int fu = INF, z = INF;
        sort(a.begin() + 1, a.end());
        for(int i = 1; i <= n; i++) {
            if(a[i] < 0 && fu == INF) {
                fu = a[i];
                vis[i] = true;
                break;
            }
        }
        for(int i = n; i >= 1; i--) {
            if(a[i] >= 0 && z == INF) {
                z = a[i];
                vis[i] = true;
                break;
            }
        }
        for(int i = 1; i <= n; i++) {
            if(!vis[i]) {
                if(a[i] >= 0) {
                    ans.push_back(Node(fu, a[i]));
                    fu -= a[i];
                } else {
                    ans.push_back(Node(z, a[i]));
                    z -= a[i];
                }
            }
        }
        ans.push_back(Node(z, fu));
    }

    return ans;
}

vector<int> generateInput(int n) {
    vector<int> a(n + 1);
    for(int i = 1; i <= n; i++) {
        a[i] = rand() % 200000 - 100000;
    }
    return a;
}