#pragma once

#include <vector>
#include <queue>
#include <map>

#define INF (1 << 24)
#define MASK (1 << 10)-1
#define fr first
#define sc second

using namespace std;

typedef pair<double,double> S;
typedef pair<S,int> P;

struct edge{ 
    double to,time; edge(){}
    edge(double to,double time):to(to),time(time){}
};

double baseline(double n, double m, double p, double a, double b, vector<double> ti, vector<vector<edge>> info) {
    double timed[101][1500];
    for(int i=0;i<101;i++){
        for(int j=0;j<1500;j++) timed[i][j] = INF;
    }

    priority_queue<P,vector<P>,greater<P>> que;
    que.push(P(S(0,a),MASK));
    timed[(int)a][MASK] = 0;

    while(!que.empty()){
        P p = que.top(); que.pop();
        double now = p.fr.sc, t = p.fr.fr;
        int bit = p.sc;

        if(now == b) return t;

        for(int i=0;i<info[(int)now].size();i++){
            edge e = info[(int)now][i];
            for(int j=0;j<n;j++){
                if(bit >> j & 1){
                    if(e.time/ti[j] + t < timed[(int)e.to][bit & ~(1<<j)]){
                        que.push(P(S(e.time/ti[j]+t,e.to),bit & ~(1<<j)));
                        timed[(int)e.to][bit & ~(1<<j)] = e.time / ti[j] + t;
                    }
                }
            }
        }
    }
    return -1;
}

vector<vector<edge>> generateInput(int n, int m) {
    vector<vector<edge>> info(m);
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            if(i != j) {
                info[i].push_back(edge(j, rand() % 100 + 1));
            }
        }
    }
    return info;
}