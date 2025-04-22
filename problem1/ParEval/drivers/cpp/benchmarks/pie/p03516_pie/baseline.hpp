#pragma once

#include<vector>
#include<algorithm>

using namespace std;

#define ll long long

const int maxN=320;
const int Mod=1e9+7;

int baseline(int n, vector<int>& D) {
    vector<vector<vector<int>>> F(maxN, vector<vector<int>>(maxN, vector<int>(2, 0)));
    vector<int> Fac(maxN), Ifc(maxN);

    Fac[0]=Ifc[0]=1;
    for (int i=1;i<maxN;i++) Fac[i]=1ll*Fac[i-1]*i%Mod;
    Ifc[maxN-1]=1;
    for (int i=maxN-2;i>=1;i--) Ifc[i]=1ll*Ifc[i+1]*(i+1)%Mod;

    bool fullring=1;
    for (int i=1;i<=n;i++) fullring&=(D[i]==2);

    if (fullring) {
        return 1ll*Fac[n-1]*Ifc[2]%Mod;
    }

    F[0][0][0]=1;
    for (int i=1;i<=n;i++)
        for (int j=0;j<=i;j++)
            for (int k=0;k<=1;k++) {
                F[i][j][k]=F[i-1][j][k];
                if ((D[i]>=2)&&(j>0)) F[i][j][k]=(1ll*F[i-1][j-1][k]*(D[i]-1)%Mod+F[i][j][k])%Mod;
                if ((D[i]>=3)&&(j>0)&&(k==1)) F[i][j][k]=(1ll*F[i-1][j-1][0]*(D[i]-1)%Mod*(D[i]-2)%Mod+F[i][j][k])%Mod;
            }

    int Ans=0;
    for (int i=3;i<=n;i++) Ans=(Ans+1ll*F[n][i][1]*Fac[i-1]%Mod*Ifc[2]%Mod*Fac[n-i-1]%Mod)%Mod;
    for (int i=1;i<=n;i++) Ans=1ll*Ans*Ifc[D[i]-1]%Mod;

    return Ans;
}

vector<int> generateInput(int n) {
    vector<int> D(n+1);
    for (int i=1; i<=n; i++) {
        D[i] = 3; // Maximize problem scale by setting degree to 3
    }
    return D;
}