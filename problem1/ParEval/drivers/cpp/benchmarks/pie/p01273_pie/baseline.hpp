#pragma once

#include<vector>
#include<algorithm>

using namespace std;

typedef vector<int> vi;
typedef pair<int,int> pii;

class UnionFind{
    vi a;
    int root(int x){ return ~a[x]?a[x]=root(a[x]):x; }
public:
    UnionFind(int n):a(n,-1){}
    bool find(int x,int y){ return root(x)==root(y); }
    bool unite(int x,int y){ return find(x,y)?0:(a[root(y)]=root(x),1); }
};

int baseline(int n, int m, vector<pair<int, pii>>& packets) {
    sort(packets.begin(), packets.end());

    int ans = 1;
    UnionFind link(n + 1);
    for(int i = 0; i < m; i++) {
        int src = packets[i].second.first, dst = packets[i].second.second;
        if (link.find(1, src)) ans += link.unite(src, dst);
    }
    return ans;
}

vector<pair<int, pii>> generateInput(int n, int m) {
    vector<pair<int, pii>> packets;
    for(int i = 1; i <= m; i++) {
        int src = i % n + 1;
        int dst = (i + 1) % n + 1;
        packets.push_back({i, {src, dst}});
    }
    return packets;
}