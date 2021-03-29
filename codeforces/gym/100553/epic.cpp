/***************************************************************
	File name: epic.cpp
	Author: huhao
	Create time: Sun 08 Nov 2020 07:42:26 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
#include<vector>
#include<map>
const int N=50010;
struct trans
{
	int n,t[N][3],o[N];
	operator int(){ return n; }
	trans &operator=(int N){ n=N; return *this; }
	int &operator[](int p){ return o[p]; }
	int &operator()(int p,int v){ return t[p][v]; }
	trans &operator++(int _){ n++; return *this; }
} a,b;
#define info std::vector<int>
std::map<info,int> t;
int solve(info E)
{
	if(E.empty()) return 1;
	std::sort(E.begin(),E.end());
	if(t.count(E)) return t[E];
	b++; int u=b; t[E]=u;
	int c[3]={0,0,0},mx=0;
	for(auto i:E) c[a[i]]++;
	fr(i,1,2) if(c[i]>c[mx]) mx=i;
	mx=(mx+1)%3; b[u]=mx;
	info e[3];
	for(auto i:E) e[a[i]].push_back(a(i,mx));
	fr(i,0,2) b(u,i)=solve(e[i]);
	return u;
}
int main()
{
	freopen("epic.in","r",stdin); freopen("epic.out","w",stdout);
	a=read();
	fr(i,1,a)
	{
		while(1)
		{
			switch(a[i])
			{
				case 'R': a[i]=0; goto ex;
				case 'P': a[i]=1; goto ex;
				case 'S': a[i]=2; goto ex;
				default: a[i]=getchar();
			}
		}
		ex: fr(j,0,2) a(i,j)=read();
	}
	info e;
	fr(i,1,a) e.push_back(i);
	solve(e);
	printf("%d\n",(int)b);
	fr(i,1,b) printf("%c %d %d %d\n","RPS"[b[i]],b(i,0),b(i,1),b(i,2));
	return 0;
}
