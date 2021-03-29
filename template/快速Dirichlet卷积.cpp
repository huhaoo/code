/***************************************************************
	File name: 快速Dirichlet卷积.cpp
	Author: huhao
	Create time: Tue 14 Jan 2020 04:56:34 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
/*
 * 代码是 f=g*I  f=g*mu
 * 视为u=\prod p_i^c_i，可看做高维前缀和/各种奇奇怪怪的东西
 */
const int N=10000010;
int p[N],c,v[N],n;
#define i64 long long
i64 f[N],g[N];
int main()
{
	n=read();
	fr(i,1,n) g[i]=read();
	fr(i,2,n)
	{
		if(!v[i]) p[++c]=i;
		fr(j,1,c)
			if(i*p[j]<=n)
			{
				v[i*p[j]]=1;
				if(i%p[j]==0) break;
			}
	}
	fr(i,1,n) f[i]=g[i];
	fr(i,1,c) fr(j,1,n/p[i]) f[j*p[i]]+=f[j];
	fr(i,1,n) printf("%lld%c",f[i],i==n?'\n':' ');// f=g*I
	fr(i,1,n) f[i]=g[i];
	fr(i,1,c) fd(j,n/p[i],1) f[j*p[i]]-=f[j];
	fr(i,1,n) printf("%lld%c",f[i],i==n?'\n':' ');// f=g*mu
	return 0;
}
/*
6
1 2 3 4 5 6
 */
