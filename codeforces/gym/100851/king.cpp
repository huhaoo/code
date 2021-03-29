/***************************************************************
	File name: king.cpp
	Author: huhao
	Create time: Thu 19 Nov 2020 10:22:59 AM CST
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
const int N=100030;
int n,m,u[N],v[N],f[N],F[N],p[N],d[N],D,_f[N];
std::vector<int> e[N];
void dfs(int u)
{
	for(auto v:e[u]) if(v!=1&&!f[v]){ f[v]=u; dfs(v); } else{ m++; ::u[m]=u; ::v[m]=v; }
}
void Dfs(int t)
{
	if(t==m+1)
	{
/*		fr(i,1,n) printf("%d%c",_f[i],i==n?'\n':' ');
		fr(i,1,n) printf("%d%c",d[i],i==n?'\n':' ');
		printf("%d\n",D);*/
		if(D!=n) return ;
		int u=f[1],c=1,C=0;
		while(u!=1)
		{
			while(f[u]!=1&&!p[f[u]]&&!p[u]){ F[u]+=F[f[u]]; f[u]=f[f[u]]; }
			c+=F[u]; u=f[u]; C++;
		}
		if(C>80){ printf("%d\n",C); exit(1); }
		if(c==n)
		{
			static int a[N];
			a[1]=1;
			fr(i,1,n) a[i+1]=_f[a[i]];
			fd(i,n+1,1) printf("%d%c",a[i],i==1?'\n':' ');
			exit(0);
		}
		return ;
	}
	Dfs(t+1);
	int k=f[v[t]];
#define modify(x,y) D-=(x&&d[x]==1),d[x]+=y,D+=(x&&d[x]==1)
	modify(f[v[t]],-1); f[v[t]]=u[t]; _f[v[t]]=u[t]; modify(f[v[t]],1);
	Dfs(t+1);
	modify(f[v[t]],-1); f[v[t]]=k; _f[v[t]]=k; modify(f[v[t]],1);
}
int main()
{
	freopen("king.in","r",stdin); freopen("king.out","w",stdout);
	n=read();
	fr(i,1,read()){ int u=read(),v=read(); e[u].push_back(v); }
	dfs(1);
	fr(i,2,n) if(!f[i])
	{
		printf("There is no route, Karl!\n");
		return 0;
	}
	fr(i,1,m) p[v[i]]=1;
	fr(i,1,n) d[f[i]]++;
	fr(i,1,n) if(d[i]==1) D++;
	fr(i,1,n){ F[i]=1; _f[i]=f[i]; }
	Dfs(1);
	printf("There is no route, Karl!\n");
	return 0;
}
