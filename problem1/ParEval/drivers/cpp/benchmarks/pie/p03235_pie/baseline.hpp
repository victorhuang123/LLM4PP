#pragma once

#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;
const int N=2e5+10;
int m0[N<<2],m1[N<<2];
#define mid ((l+r)>>1)
void psup(int o){m0[o]=max(m0[o<<1],m0[o<<1|1]),m1[o]=max(m1[o<<1],m1[o<<1|1]);}
void modif(int o,int l,int r,int x,int y,bool oo)
{
	if(l==r){!oo?m0[o]=y:m1[o]=y;return;}
	if(x<=mid) modif(o<<1,l,mid,x,y,oo);
	else modif(o<<1|1,mid+1,r,x,y,oo);
	psup(o);
}
int quer(int o,int l,int r,int ll,int rr,bool oo)
{
	if(ll<=l&&r<=rr) return !oo?m0[o]:m1[o];
	int an=-(1<<20);
	if(ll<=mid) an=max(an,quer(o<<1,l,mid,ll,rr,oo));
	if(rr>mid) an=max(an,quer(o<<1|1,mid+1,r,ll,rr,oo));
	return an;
}

vector<bool> baseline(int n, const vector<int>& a, const vector<bool>& b)
{
	memset(m1,-0x3f3f3f,sizeof(m1));
	vector<bool> an(n);
	int sm = 0;
	for(int i=1,ma=0;i<=n;++i)
	{
		if(ma<a[i]) ma=a[i],++sm;
	}
	for(int i=n;i;--i)
	{
		int f[N][2];
		f[i][1]=-(1<<20);
		int xx=b[i]+1+max(0,quer(1,1,n,a[i],n,0)),yy=b[i]+1+max(0,quer(1,1,n,a[i],n,1));
		f[i][xx&1]=max(f[i][xx&1],xx);
		f[i][yy&1]=max(f[i][yy&1],yy);
		modif(1,1,n,a[i],f[i][0],0);
		modif(1,1,n,a[i],f[i][1],1);
	}
	int c0=0,c1=0,mi0=0,mi1=0;
	for(int i=1,j=sm;i<=n;++i)
	{
		j-=b[i];
		modif(1,1,n,a[i],0,0);
		modif(1,1,n,a[i],-(1<<20),1);
		int x=c0+(a[i]>=mi0)-c1+j;
		bool o=0;
		if(quer(1,1,n,max(mi1,1),n,x&1)<x)
		{
			x=c1-(c0+(a[i]>=mi0))+j;
			o=x<0||quer(1,1,n,max(mi0,a[i]),n,x&1)<x;
		}
		if(o) an[i]=1,c1+=a[i]>=mi1,mi1=max(mi1,a[i]);
		else c0+=a[i]>=mi0,mi0=max(mi0,a[i]);
	}
	c0=c1=0;
	for(int i=1,mm0=0,mm1=0;i<=n;++i)
	{
		if(!an[i])
		{
			if(mm0<a[i]) mm0=a[i],++c0;
		}
		else
		{
			if(mm1<a[i]) mm1=a[i],++c1;
		}
	}
	if(c0!=c1) return vector<bool>();
	return an;
}

vector<int> generateInput(int n)
{
	vector<int> a(n+1);
	for(int i=1;i<=n;++i) a[i]=i;
	return a;
}