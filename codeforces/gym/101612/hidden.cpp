/***************************************************************
	File name: hidden.cpp
	Author: huhao
	Create time: Mon 02 Nov 2020 02:08:23 PM CST
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
const int N=100010;
int n,f[N],v[N],p[N],d[N],m,ans,F[N];
int dfs(int u){ return !d[u]&&u?d[u]=dfs(f[u])+1:d[u]; }
int getf(int u){ return u==F[u]?u:F[u]=getf(F[u]); }
int cmp(int u,int v){ return d[u]>d[v]; }
int main()
{
	freopen("hidden.in","r",stdin); freopen("hidden.out","w",stdout);
	n=read();
	F[1]=1;
	fr(i,2,n) f[i]=read();
	fr(i,2,n) if(f[i]) F[i]=f[i]; else F[i]=i;
	fr(i,1,n) if(!d[i]) dfs(i);
	d[1]=N;
	fr(i,1,n) p[i]=i;
	std::sort(p+1,p+n+1,cmp);
	fr(i,1,n) if(f[p[i]]&&!v[p[i]]&&!v[f[p[i]]]){ ans++; v[p[i]]=v[f[p[i]]]=1; }
	fr(i,1,n) if(!v[i]) p[++m]=i;
//	fr(i,1,n) printf("%d%c",getf(i),i==n?'\n':' ');
//	fr(i,1,n) printf("%d%c",v[i],i==n?'\n':' ');
//	fr(i,1,n) printf("%d%c",p[i],i==n?'\n':' ');
//	fr(i,1,n) if(d[i]==1) printf("%d ",i);
//	putchar(10);
	std::sort(p+1,p+m+1,cmp);
	for(int i=m,j=1;i>j&&d[p[i]]==1;i--)
	{
		int x=j;
		while((v[p[x]]||getf(p[x])==p[i])&&x<i) x++;
		if(x<i)
		{
			v[p[i]]=v[p[x]]=1; ans++; f[p[i]]=p[x]; F[p[i]]=p[x];
		}
		while(v[p[j]]&&j<i) j++;
	}
	fr(i,2,n) if(!f[i]) f[i]=F[i]=1;
	printf("%d\n",ans);
	fr(i,2,n) printf("%d%c",f[i],i==n?'\n':' ');
//	fr(i,1,n) printf("%d%c",getf(i),i==n?'\n':' ');
	return 0;
}
