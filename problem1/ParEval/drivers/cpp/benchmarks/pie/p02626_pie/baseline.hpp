#pragma once

#include <vector>

std::vector<long> generateInput(int N) {
    std::vector<long> input(N);
    for (int i = 0; i < N; ++i) {
        input[i] = i + 1; // Example input, can be modified to maximize problem scale
    }
    return input;
}

long baseline(int N, long A, long B, const std::vector<long>& input) {
    long S = 0;
    long ok[2][2];

    for(int i=0;i<2;i++)for(int j=0;j<2;j++)ok[i][j]=-1;

    for(int i=2;i<N;i++) {
        long T = input[i]; S^=T;
    }

    long uA=A>>20,dA=A&(1<<20)-1;
    long uB=B>>20,dB=B&(1<<20)-1;
    long uS=S>>20,dS=S&(1<<20)-1;

    for(long k=0;k<=uA;k++) {
        for(int i=0;i<2;i++)for(int j=0;j<2;j++) {
            if(k+i>uA)continue;
            if((uA-k-i^uB+k+j)==uS&&ok[i][j]==-1)ok[i][j]=k;
        }
    }

    long ans=A;
    for(long k=0;k<1<<20;k++) {
        if(dA>=k) {
            if(((dA-k)^(dB+k)&(1<<20)-1)==dS) {
                int j=dB+k>=1<<20;
                if(ok[0][j]!=-1) {
                    long tmp=ok[0][j]<<20|k;
                    if(ans>tmp)ans=tmp;
                }
            }
        } else {
            if(((dA+(1<<20)-k)^(dB+k)&(1<<20)-1)==dS) {
                int j=dB+k>=1<<20;
                if(ok[1][j]!=-1) {
                    long tmp=ok[1][j]<<20|k;
                    if(ans>tmp)ans=tmp;
                }
            }
        }
    }

    if(ans==A)ans=-1;
    return ans;
}