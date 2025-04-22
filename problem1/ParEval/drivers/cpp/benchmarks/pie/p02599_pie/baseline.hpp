
#include<bits/stdc++.h>
using namespace std;

vector<int> baseline(int n, int m, const vector<int>& inputArray, const vector<pair<int, int>>& queries) {
    const int N = 1e6 + 10;
    int bl;
    vector<int> a(N), cnt(N), ans(m);
    vector<tuple<int, int, int>> e(m);

    for(int i=1; i<=n; i++) a[i] = inputArray[i-1];
    
    bl = sqrt(n);
    for(int i=0; i<m; i++)
        e[i] = {queries[i].first, queries[i].second, i};
    
    sort(e.begin(), e.end(), [&](const auto& x, const auto& y) {
        int bx = get<0>(x)/bl, by = get<0>(y)/bl;
        return bx != by ? bx < by : get<1>(x) < get<1>(y);
    });

    int res=0, curL=1, curR=0;
    auto add = [&](int i) { if(++cnt[a[i]] == 1) res++; };
    auto remove = [&](int i) { if(--cnt[a[i]] == 0) res--; };

    for(auto& [L,R,p] : e) {
        while(curL < L) remove(curL++);
        while(curL > L) add(--curL);
        while(curR < R) add(++curR);
        while(curR > R) remove(curR--);
        ans[p] = res;
    }

    return ans;
}

