#pragma once

#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

#define rep(i, n) for(int i = 0; i < (n); i++)

#define rep1(i, n) for(int i = 1; i <= (n); i++)

#define pb push_back

#define mp make_pair

const int cm = 1 << 17;

char cn[cm], *ci = cn + cm, ct;

inline char getcha() {

	if (ci - cn == cm) { fread_unlocked(cn, 1, cm, stdin); ci = cn; }

	return *ci++;

}

inline int getint() {

	int A = 0;

	if (ci - cn + 16 > cm) while ((ct = getcha()) >= '0') A = A * 10 + ct - '0';

	else while ((ct = *ci++) >= '0') A = A * 10 + ct - '0';

	return A;

}

ll baseline(int N, int M, vector<int>& A, vector<pair<int, int>>& BC) {

	sort(A.begin(), A.end());

	sort(BC.begin(), BC.end());

	vector<int> B(N, 0);

	int kazu = 0;

	for (int i = M - 1; i >= 0; i--) {

		rep(j, BC[i].second) {

			if (kazu >= N) break;

			B[kazu] = BC[i].first;

			kazu++;

		}

	}

	ll kotae = 0;

	rep(i, N) kotae += max(A[i], B[i]);

	return kotae;

}

vector<int> generateA(int N) {

	vector<int> A(N);

	rep(i, N) A[i] = rand() % 1000000000;

	return A;

}

vector<pair<int, int>> generateBC(int M) {

	vector<pair<int, int>> BC(M);

	rep(i, M) {

		BC[i].second = rand() % 100000 + 1;

		BC[i].first = rand() % 1000000000;

	}

	return BC;

}