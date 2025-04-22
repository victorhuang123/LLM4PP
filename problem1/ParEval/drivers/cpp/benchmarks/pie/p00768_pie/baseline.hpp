#pragma once

#include<bits/stdc++.h>

using namespace std;

#define rep(i,n) for(int i=0;i<(int)(n);++i)

#define pb(a) push_back(a)

#define mp(a,b) make_pair(a,b)

#define ALL(a) (a).begin(),(a).end()

#define F first

#define S second

typedef pair<int,int> PI;

vector<int> baseline(int m, int t, int p, int r, const vector<vector<int>>& submissions) {
  int app[400][400];
  int pena[400];
  memset(app,0,sizeof(app));
  memset(pena,0,sizeof(pena));  

  vector<int> sol(10000);

  rep(i,r){
    int mk = submissions[i][0];
    int tk = submissions[i][1];
    int pk = submissions[i][2];
    int jk = submissions[i][3];
    if(jk==0){
      pena[tk] += app[tk][pk]*20+mk;
      ++sol[tk];
    }else{
      ++app[tk][pk];
    }
  }

  vector<pair<PI,int> > team;

  rep(i,t){
    team.pb(mp(mp(-sol[i+1],pena[i+1]),-i-1));
  }

  sort(ALL(team));
  vector<int> result;
  rep(i,t){
    if(i){
      if(team[i-1].F == team[i].F) result.pb(-1); // Use -1 to represent '='
      else result.pb(-2); // Use -2 to represent ','
    }
    result.pb(-team[i].S);
  }
  return result;
}

vector<vector<int>> generateInput(int m, int t, int p, int r) {
  vector<vector<int>> submissions(r, vector<int>(4));
  rep(i, r) {
    submissions[i][0] = rand() % m + 1; // mk
    submissions[i][1] = rand() % t + 1; // tk
    submissions[i][2] = rand() % p + 1; // pk
    submissions[i][3] = rand() % 2;    // jk
  }
  return submissions;
}