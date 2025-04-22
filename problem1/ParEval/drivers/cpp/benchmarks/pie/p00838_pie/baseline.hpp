#pragma once

#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

const int mov[24][6]= {
  {0,1,2,3,4,5},{0,2,4,1,3,5},{0,4,3,2,1,5},{0,3,1,4,2,5},
  {3,1,0,5,4,2},{3,0,4,1,5,2},{3,4,5,0,1,2},{3,5,1,4,0,2},
  {5,1,3,2,4,0},{5,3,4,1,2,0},{5,4,2,3,1,0},{5,2,1,4,3,0},
  {2,1,5,0,4,3},{2,5,4,1,0,3},{2,4,0,5,1,3},{2,0,1,4,5,3},
  {4,0,2,3,5,1},{4,2,5,0,3,1},{4,5,3,2,0,1},{4,3,0,5,2,1},
  {1,0,3,2,5,4},{1,3,5,0,2,4},{1,5,2,3,0,4},{1,2,0,5,3,4}
};

struct Cube {
	vector<int> num;
};

int cnt;
map<string,int> id;

int ID(const string& st) {
	if (id[st] == 0) return id[st] = ++cnt;
	return id[st];
}

void dfs(int dep, int n, const vector<Cube>& c, vector<Cube>& now, int &ans) {
	if (n == dep) {
		int ans1 = 0;
		for (int j = 0; j < 6; ++j) {
			vector<int> count(30, 0);
			for (int i = 0; i < n; ++i) ++count[now[i].num[j]];
			int up = 0;
			for (int i = 1; i <= cnt; ++i) up = max(up, count[i]);
			ans1 += n - up;
		}
		ans = min(ans, ans1);
		return ;	
	}
	for (int i = 0; i < 24; ++i) {
		for (int j = 0; j < 6; ++j) {
			now[dep].num[j] = c[dep].num[mov[i][j]];
		}
		dfs(dep + 1, n, c, now, ans);
	}
}

int baseline(const vector<Cube>& c) {
	int n = c.size();
	vector<Cube> now(n);
	id.clear();
	cnt = 0;
	int ans = (int)1e9;
	now[0] = c[0];
	dfs(1, n, c, now, ans);
	return ans;
}

vector<Cube> generateInput() {
	vector<Cube> cubes(5);
	for (int i = 0; i < 5; ++i) {
		cubes[i].num.resize(6);
		for (int j = 0; j < 6; ++j) {
			cubes[i].num[j] = ID(to_string(i * 6 + j));
		}
	}
	return cubes;
}