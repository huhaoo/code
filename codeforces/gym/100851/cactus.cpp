/***************************************************************
	File name: cactus.cpp
	Author: huhao
	Create time: Thu 26 Nov 2020 03:38:18 PM CST
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
#include<vector>
const int N=100010;
int n,dfn[N],low[N],f[N],Dfn,m;
std::vector<int> e[N],E[N];
void dfs(int u)
{
	low[u]=dfn[u]=++Dfn;
	for(auto v:E[u])
		if(v!=f[u])
		{
			if(!dfn[v])
			{
				f[v]=u; dfs(v); low[u]=std::min(low[u],low[v]);
			}
			else if(dfn[v]<dfn[u])
			{
				m++; low[u]=std::min(low[u],dfn[v]); int i=u;
				while(i!=f[v]){ e[m].push_back(i); e[i].push_back(m); i=f[i]; }
			}
		}
	if(u!=1&&dfn[u]==low[u]){ e[u].push_back(f[u]); e[f[u]].push_back(u); }
}
void Dfs(int u)
{
	for(auto v:e[u]) if(f[u]!=v){ f[v]=u; Dfs(v); }
}
i64 ans,Ans;
int w[N];
void _solve(int u)
{
	w[u]=(u<=n);
	for(auto v:e[u]) if(f[v]==u)
	{
		_solve(v); w[u]+=w[v];
	}
}
void solve(int u)
{
	w[u]=1;
	for(auto v:e[u]) if(f[v]==u&&v<=n)
	{
		solve(v); w[u]+=w[v];
	}
}
void Solve(int u,int W)
{
	w[u]=W;
	for(auto v:e[u]) if(f[v]==u&&v<=n) Solve(v,W);
}
int main()
{
	freopen("cactus.in","r",stdin); freopen("cactus.out","w",stdout);
	n=read();
	fr(t,1,read())
	{
		static int a[N],A; A=read();
		fr(i,1,A) a[i]=read();
		fr(i,2,A){ E[a[i]].push_back(a[i-1]); E[a[i-1]].push_back(a[i]); ans--; }
	}
	m=n; dfs(1); memset(f,0,sizeof(f)); Dfs(1);
//	fr(i,1,m) for(auto j:e[i]) if(i<j) printf("%d %d\n",i,j);
	solve(1); Solve(1,w[1]); Ans+=(i64)w[1]*(w[1]-1)/2-(w[1]-1);
	fr(i,n+1,m) for(auto j:e[i]) if(f[j]==i){ solve(j); Ans+=(i64)w[j]*(w[j]-1)/2-(w[j]-1); Solve(j,w[j]); }
	fr(i,n+1,m)
	{
		i64 s=0,c=Ans;
		for(auto j:e[i]){ s+=w[j]; c-=(i64)(w[j]-1)*w[j]/2-(w[j]-1); }
		ans+=(s*(s-1)/2-(s-1))*e[i].size();
		ans+=c*e[i].size();
//		printf("%d %d\n",s,e[i].size());
	}
//	printf("%d\n",Ans);
	_solve(1);
//	fr(i,1,n) printf(" %d %d\n",f[i],w[i]);
	fr(i,1,n) if(f[i]<=n) ans+=(i64)w[i]*(n-w[i]);
	printf("%lld\n",ans);
	return 0;
}
