#pragma once

#include <vector>

const int MOD = 998244353;
const int INV2 = (MOD + 1) >> 1;

int add(int x, int y) {return (x + y >= MOD ? x + y - MOD : x + y);}
int sub(int x, int y) {return (x - y < 0 ? x - y + MOD : x - y);}
int mul(int x, int y) {return 1LL*x*y%MOD;}

int pow_mod(int b, int p) {
	int ret = 1;
	for(int i=p;i;i>>=1,b=mul(b,b))
		if( i & 1 ) ret = mul(ret,b);
	return ret;
}

struct node{
	int k, b;
	node() : k(0), b(0) {}
	node(int _k, int _b) : k(_k), b(_b) {}
	int get(int x) {return add(mul(k, x), b);}
	friend node operator + (node a, node b) {
		return node(add(a.k, b.k), add(a.b, b.b));
	}
	friend node operator - (node a, node b) {
		return node(sub(a.k, b.k), sub(a.b, b.b));
	}
	friend node operator * (node a, int k) {
		return node(mul(a.k, k), mul(a.b, k));
	}
	friend node operator / (node a, int k) {
		return a * pow_mod(k, MOD - 2);
	}
};

void fwt(std::vector<node> &A, int m, int type) {
	int n = (1 << m), f = (type == 1 ? 1 : INV2);
	for(int i=1;i<=m;i++) {
		int s = (1 << i), t = (s >> 1);
		for(int j=0;j<n;j+=s)
			for(int k=0;k<t;k++) {
				node x = A[j+k], y = A[j+k+t];
				A[j+k] = (x + y)*f, A[j+k+t] = (x - y)*f;
			}
	}
}

std::vector<int> baseline(int N, int M, const std::vector<node> &A, const std::vector<node> &B, const std::vector<node> &C) {
	std::vector<node> f(M);
	int S = 0;
	for(int i=0;i<M;i++) S = add(S, A[i].b);
	S = pow_mod(S, MOD - 2);
	std::vector<node> A_mod = A;
	for(int i=0;i<M;i++) A_mod[i].b = sub(i == 0 ? 1 : 0, mul(A[i].b, S));
	std::vector<node> B_mod = B;
	for(int i=0;i<M;i++) B_mod[i].b = 1;
	std::vector<node> C_mod = C;
	C_mod[0].b = MOD - 1;
	fwt(A_mod, N, 1), fwt(B_mod, N, 1), fwt(C_mod, N, 1);
	int tmp = mul(B_mod[0].b, pow_mod(C_mod[0].b, MOD-2));
	for(int i=1;i<M;i++)
		f[i] = (B_mod[i] - C_mod[i]*tmp) / A_mod[i].b;
	f[0].k = 1; fwt(f, N, -1);
	int x = sub(0, mul(pow_mod(f[0].k, MOD-2), f[0].b));
	std::vector<int> result(M);
	for(int i=0;i<M;i++) result[i] = f[i].get(x);
	return result;
}

std::vector<node> generateInput(int M) {
	std::vector<node> input(M);
	for(int i = 0; i < M; ++i) {
		input[i] = node(1, i);
	}
	return input;
}