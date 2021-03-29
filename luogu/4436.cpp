/****************************************************************
	File name: 4436.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 12/17/2018, 7:20:10 PM
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define N 1000010
int n,m,q,f[N],y[N],a[N],l[N],r[N];
void dfs(int x)
{
	while(1)
	{
		if(l[x]>1&&a[l[x]-1]>=l[x]&&a[l[x]-1]<=r[x])
		{
			dfs(l[x]-1);
			l[x]=l[l[x]-1];
			continue;
		}
		if(r[x]<=m&&a[r[x]]>=l[x]&&a[r[x]]<=r[x])
		{
			dfs(r[x]+1);
			r[x]=r[r[x]+1];
			continue;
		}
		break;
	}
}
int main()
{
	n=read();m=read();q=read();
	fr(i,1,m)
	{
		int a=read(),b=read();
		y[a]=b;
	}
	f[1]=1;
	fr(i,1,n-1)
		f[i+1]=y[i]?f[i]+1:f[i];
	fr(i,1,n)if(y[i])
		a[f[i]]=f[y[i]];
//	fr(i,1,n)printf("%d%c",f[i],i==n?'\n':' ');
	fr(i,1,m+1)l[i]=r[i]=i;
	fr(i,1,m+1)dfs(i);
	while(q--)
	{
		int x=read(),y=read();
		if(l[f[x]]<=f[y]&&r[f[x]]>=f[y])
			printf("YES\n");
		else
			printf("NO\n");
	}
	return 0;
}