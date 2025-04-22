#pragma once

#include<vector>
#include<cstring>
using namespace std;

typedef long long ll;
const int maxn=100005,maxm=400005;
int last[maxn],pre[maxm],other[maxm],t,cal[maxn],vis[maxn],q[maxn],head,tail;

void add(int x,int y){++t;pre[t]=last[x];last[x]=t;other[t]=y;}

ll baseline(int n, int m, vector<pair<int, int>>& edges) {
    ll I=0,P=0,Q=0;
    memset(last,0,sizeof(last));t=0;memset(vis,0,sizeof(vis));
    memset(pre,0,sizeof(pre));memset(other,0,sizeof(other));

    for(int i=0;i<m;++i){
        int x=edges[i].first,y=edges[i].second;
        add(x,y);add(y,x);
    }

    for(int i=1;i<=n;++i)if(!vis[i]){
        head=tail=0;q[++tail]=i;cal[i]=0;vis[i]=1;
        bool flag=1;
        while(head<tail){
            int u=q[++head];
            for(int j=last[u];j;j=pre[j]){
                int v=other[j];
                if(!vis[v]){
                    q[++tail]=v;vis[v]=1;cal[v]=cal[u]+1;
                }
                else{
                    if((cal[v]-cal[u])%2==0)flag=0;
                }
            }
        }
        if(head==1){++I;continue;}
        if(flag)++Q;
        else ++P;
    }
    return 2ll*I*n-I*I+P*P+2ll*P*Q+2ll*Q*Q;
}

vector<pair<int, int>> generateInput(int n, int m) {
    vector<pair<int, int>> edges;
    for(int i = 1; i <= m; ++i) {
        int u = i % n + 1;
        int v = (i + 1) % n + 1;
        edges.push_back({u, v});
    }
    return edges;
}