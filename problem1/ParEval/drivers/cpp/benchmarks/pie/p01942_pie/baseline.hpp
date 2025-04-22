#pragma once

#include<bits/stdc++.h>

using namespace std;

template<typename T> 
struct BIT2D{
  int n,m;
  T d;
  vector<vector<T> > bit;

  BIT2D():n(-1),m(-1){}
  BIT2D(int n_,int m_,T d_):n(n_),m(m_),d(d_),bit(n_+1,vector<T>(m+1,d_)){}

  T sum(int i,int j){
    T s=d;
    for(int x=i;x>0;x-=(x&-x))
      for(int y=j;y>0;y-=(y&-y))
        s+=bit[x][y];
    return s;
  }

  void add(int i,int j,T a){
    if(i==0||j==0) return;
    for(int x=i;x<=n;x+=(x&-x))
      for(int y=j;y<=m;y+=(y&-y))
        bit[x][y]+=a;
  }

  T sum(int x1,int y1,int x2,int y2){
    return sum(x1,y1)-sum(x1,y2)-sum(x2,y1)+sum(x2,y2);
  }
};

pair<int, int> baseline(int h, int w, int t, int q, vector<tuple<int, int, int, int, int, int>>& queries) {
  BIT2D<int> beet(h+100,w+100,0);
  BIT2D<int> ushi(h+100,w+100,0);
  typedef pair<int,int> P;
  typedef pair<int,P> PP;
  queue<PP> qq; 

  for(auto& query : queries){
    int a = get<0>(query), c = get<1>(query), x1 = get<2>(query), y1 = get<3>(query);
    while(!qq.empty()&&qq.front().first<=a){
      P p=qq.front().second;qq.pop();
      int x=p.first,y=p.second;
      assert(beet.sum(x-1,y-1,x,y)==1);
      beet.add(x,y,-1);
      assert(ushi.sum(x-1,y-1,x,y)==0);
      ushi.add(x,y,1);
    }
    if(c==0){
      assert(beet.sum(x1-1,y1-1,x1,y1)==0);
      beet.add(x1,y1,1);
      qq.push(PP(a+t,P(x1,y1)));
    }
    if(c==1){
      if(ushi.sum(x1-1,y1-1,x1,y1)==0) continue;
      ushi.add(x1,y1,-1);
    }
    if(c==2){
      int x2 = get<4>(query), y2 = get<5>(query);
      x1--;y1--;
      return {ushi.sum(x1,y1,x2,y2), beet.sum(x1,y1,x2,y2)};
    }
  }
  return {0, 0};
}

vector<tuple<int, int, int, int, int, int>> generateInput(int h, int w, int t, int q) {
  vector<tuple<int, int, int, int, int, int>> queries;
  for(int i = 0; i < q; i++) {
    int a = rand() % 1000000;
    int c = rand() % 3;
    int x1 = rand() % h + 1;
    int y1 = rand() % w + 1;
    int x2 = rand() % h + 1;
    int y2 = rand() % w + 1;
    queries.push_back({a, c, x1, y1, x2, y2});
  }
  return queries;
}