#pragma once

#include<vector>
#include<queue>
#include<algorithm>
#include<climits>

using namespace std;

const int MAXN=1e5;

struct NODE{
	int p,val;
	NODE(){}
	NODE(int a,int b){p=a;val=b;}
};

struct QUEUE{
	int u,p;
	long long val;
	QUEUE(){}
	QUEUE(int a,int b,long long c){u=a;p=b;val=c;}
};

inline int G(int p){return p==1;}

int baseline(int n_pnt, int n_edg, vector<pair<int,int> > lnk[MAXN+5]) {
    long long vis[2][MAXN+5];
    fill(vis[0],vis[0]+MAXN+5,LLONG_MAX);
    fill(vis[1],vis[1]+MAXN+5,LLONG_MAX);

    long long MIN=-LLONG_MAX,MAX=LLONG_MAX;

    queue<QUEUE> que;
    que.push(QUEUE(1,1,0));

    while(!que.empty()) {
        QUEUE fro=que.front();que.pop();
        for(int i=0;i<lnk[fro.u].size();i++) {
            int v=lnk[fro.u][i].first,l=lnk[fro.u][i].second;
            long long val=l-fro.val;int p=fro.p==1? -1:1;
            if(vis[G(p)][v]!=LLONG_MAX) {
                if(val!=vis[G(p)][v]) {
                    return 0;
                }
                else
                    continue;
            }
            vis[G(p)][v]=val;
            if(G(p))
                MIN=max(MIN,max((long long)0,-vis[1][v]));
            else
                MAX=min(MAX,vis[0][v]);
            que.push(QUEUE(v,p,val));
        }
    }

    long long ans=-1;
    for(int i=1;i<=n_pnt;i++)
        if(vis[0][i]!=LLONG_MAX && vis[1][i]!=LLONG_MAX) {
            int res=(vis[0][i]-vis[1][i])/2;
            if(res<0) return 0;
            if(ans==-1) ans=res;
            if(ans!=res) return 0;
        }

    if(ans!=-1) {
        if(MIN<ans && ans<MAX)
            return 1;
        else
            return 0;
    }

    if(MAX-MIN-1<0) return 0;
    else return MAX-MIN-1;
}

vector<pair<int,int> > generateInput(int n_pnt, int n_edg) {
    vector<pair<int,int> > lnk[MAXN+5];
    for(int i=0;i<n_edg;i++) {
        int u = rand() % n_pnt + 1;
        int v = rand() % n_pnt + 1;
        int l = rand() % 1000 + 1;
        lnk[u].push_back({v, l});
    }
    return lnk[MAXN+5];
}