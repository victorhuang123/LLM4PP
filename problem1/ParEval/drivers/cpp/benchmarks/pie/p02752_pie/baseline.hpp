#pragma once

#include<cctype>
#include<cstdio>
#include<vector>
#include<cstring>

const int N=300007,P=998244353,i2=P-P/2;

void inc(int&a,int b){a+=b-P,a+=a>>31&P;}
int mul(int a,int b){return 1ll*a*b%P;}
int read(){int x=0,c=getchar();while(isspace(c))c=getchar();while(isdigit(c))(x*=10)+=c&15,c=getchar();return x;}

void dfs(int u,int dep,int& len,int& root,int fa[],std::vector<int>e[])
{
    if(dep>len) len=dep,root=u;
    for(int v:e[u]) if(v^fa[u]) fa[v]=u,dfs(v,dep+1,len,root,fa,e);
}

void dp(int u,int fa,int d,int m,int f[][3][3],std::vector<int>e[])
{
    (d==m/2? f[u][1][1]:f[u][0][0])=1;
    for(int v:e[u])
    {
        if(v==fa) continue;
        dp(v,u,d+1,m,f,e);
        int g[3][3]={0};
        for(int x=0;x<3;++x) for(int y=0;y<3;++y) for(int p=0;p<3;++p) for(int q=0;q<3;++q) for(int k=0,r,t;k<3;++k) r=std::min(2,x+p*(k==1)),t=std::min(2,y+q*(k==2)),inc(g[r][t],mul(f[u][x][y],f[v][p][q]));
        memcpy(f[u],g,36);
    }
}

int baseline(int n, std::vector<int>e[])
{
    int p,q,root,len=0,m=0,fa[N]={0},dia[N]={0},f[N][3][3]={0};
    dfs(1,1,len,root,fa,e);
    memset(fa+1,0,n<<2),len=0,dfs(root,1,len,root,fa,e);
    for(int i=root;i;i=fa[i]) dia[++m]=i;
    if(m&1) p=dia[m/2+1],dp(p,0,0,m,f,e); return mul(i2,f[p][1][1]);
    else p=dia[m/2],q=dia[m/2+1],dp(p,q,1,m,f,e),dp(q,p,1,m,f,e); return mul((1ll*f[p][1][0]+f[p][1][1]+f[p][1][2])%P,(1ll*f[q][1][0]+f[q][1][1]+f[q][1][2])%P);
}

std::vector<int> generateInput(int n) {
    std::vector<int> e[n + 1];
    for (int i = 2; i <= n; ++i) {
        e[i].push_back(i / 2);
        e[i / 2].push_back(i);
    }
    return e;
}