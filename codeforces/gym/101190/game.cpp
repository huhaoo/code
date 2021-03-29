/***************************************************************
	File name: game.cpp
	Author: huhao
	Create time: Mon 16 Nov 2020 07:33:58 PM CST
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
const int N=200010;
int n,m,f[N],d[N],q[N],l,r;
std::vector<int> e[N],E[N];
int main()
{
	freopen("game.in","r",stdin); freopen("game.out","w",stdout);
	n=read(); m=read();
	fr(i,1,m)
	{
		int u=read(),v=read();
		e[u].push_back(v+n); e[u+n].push_back(v);
		E[v+n].push_back(u); E[v].push_back(u+n);
	}
	fr(i,1,n+n)
	{
		d[i]=e[i].size();
		if(i>n&&d[i]) d[i]=1;
	}
	l=1; r=0;
	fr(i,1,n+n) if(!d[i]) q[++r]=i;
	while(l<=r)
	{
		int u=q[l++]; f[u]=1;
		for(auto v:E[u]){ d[v]--; if(!d[v]) q[++r]=v; }
	}
//	fr(i,1,n+n) printf("%d%c",f[i],i%n==0?'\n':' ');
	fr(i,1,n+n) d[i]=0;
	fr(i,1,n+n) if(f[i]) for(auto j:e[i]) if(f[j]) d[i]++;
	l=1; r=0;
	fr(i,1,n+n) if(f[i]&&!d[i]) q[++r]=i;
	while(l<=r)
	{
		int u=q[l++]; f[u]=-1;
//		printf("%d  %d\n",u,(u-1)%n+1);
		for(auto i:e[u]){ if(f[i]==-1) f[u]=1; }
		for(auto i:E[u]) if(f[i]){ d[i]--; if(d[i]>0&&f[u]==-1) d[i]=0; if(!d[i]) q[++r]=i; }
	}
	fr(i,n+1,n+n) if(d[i]>0) f[i]=-1;
	fr(i,1,n) putchar("LDW"[f[i]+1]);; putchar(10);
	fr(i,n+1,n+n) putchar("LDW"[f[i]+1]);; putchar(10);
	return 0;
}
