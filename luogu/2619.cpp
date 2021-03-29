/***************************************************************
	File name: 2619.cpp
	Author: huhao
	Create time: Wed 25 Sep 2019 11:17:21 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
const int N=100010;
int n,m,k,dw,ans;
struct edge
{
	int u,v,w,c;
	edge(int U=0,int V=0,int W=0,int C=0)
	{
		u=U;
		v=V;
		w=W;
		c=C;
	}
}e[N];
int cmp(edge a,edge b)
{
	return a.w+a.c*dw==b.w+b.c*dw?a.c<b.c:a.w+a.c*dw<b.w+b.c*dw;
}
int f[N];
int getf(int x)
{
	return x==f[x]?x:f[x]=getf(f[x]);
}
int calc(int mid)
{
	int ans=0;
	dw=mid;
	sort(e+1,e+m+1,cmp);
	fr(i,1,n)
		f[i]=i;
	fr(i,1,m)
		if(getf(e[i].u)!=getf(e[i].v))
		{
			f[getf(e[i].u)]=getf(e[i].v);
			ans+=e[i].c;
		}
	return ans;
}
int main()
{
	n=read();
	m=read();
	k=read();
	fr(i,1,m)
	{
		int u=read()+1,v=read()+1,w=read(),c=1-read();
		e[i]=edge(u,v,w,c);
	}
	int l=-100,r=100;
	while(l<r)
	{
		int mid=(l+r)>>1;
		if(calc(mid)<k)
			r=mid;
		else
			l=mid+1;
	}
	dw=l;
	fr(i,1,n)
		f[i]=i;
	sort(e+1,e+m+1,cmp);
	int ans=0;
	fr(i,1,m)
		if(getf(e[i].u)!=getf(e[i].v))
		{
			f[getf(e[i].u)]=getf(e[i].v);
			ans+=e[i].w+e[i].c*dw;
		}
	printf("%d\n",ans-dw*k);
	return 0;
}
