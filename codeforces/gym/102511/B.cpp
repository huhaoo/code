/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Wed 25 Nov 2020 11:26:48 AM CST
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
#define i64 long long
const int N=10010;
int n,h,a,b;
int x[N],y[N];
int l[N],r[N];
i64 f[N];
int main()
{
	n=read()-1; h=read(); a=read(); b=read();
	fr(i,0,n){ x[i]=read(); y[i]=read(); if(y[i]>h){ printf("impossible\n"); return 0; } }
	h-=y[0];
	fd(i,n,0){ x[i]-=x[0]; y[i]-=y[0]; }
	fr(i,0,n){ l[i]=0; r[i]=n; f[i]=1ll<<60; }
	fr(i,0,n)
	{
		while(x[r[i]]-x[i]+y[i]*2>h*2) r[i]--;
		while(x[i]-x[l[i]]+y[i]*2>h*2) l[i]++;
	}
	f[0]=h*a;
	fr(t,0,n)
	{
		for(int i=0,j=n;i<t;i++)
		{
			while(j>t&&x[t]+x[t]<x[i]+x[j])
			{
				i64 r=x[j]-x[i],d=r-(x[t]-x[i])*2,l=(h-y[t])*2;
				if(l>=r||r*r-d*d>=(l-r)*(l-r)) break;
//				printf("%d %d %d  %lld %lld %lld    %lld %lld\n",t,i,j,r,d,l,r*r-d*d,(l-r)*(l-r));
				j--;
			}
			r[i]=std::min(r[i],j);
		}
		for(int i=0,j=n;j>t;j--)
		{
			while(i<t&&x[t]+x[t]>x[i]+x[j])
			{
				i64 r=x[j]-x[i],d=r-(x[j]-x[t])*2,l=(h-y[t])*2;
				if(l>=r||r*r-d*d>=(l-r)*(l-r)) break;
				i++;
			}
			l[j]=std::max(l[j],i);
		}
	}
//	fr(i,0,n) printf(" %d %d\n",l[i],r[i]);
	fr(i,0,n) fr(j,i+1,r[i]) if(i>=l[j])
	{
//		printf(" %d %d\n",i,j);
		f[j]=std::min(f[j],f[i]+(i64)(x[j]-x[i])*(x[j]-x[i])*b+a*(h-y[j]));
	}
	if(f[n]>(1ll<<59)) printf("impossible\n");
	else printf("%lld\n",f[n]);
	return 0;
}
