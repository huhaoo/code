/***************************************************************
	File name: J.cpp
	Author: huhao
	Create time: Sun 15 Nov 2020 04:50:57 PM CST
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
#define pii std::pair<int,int>
const int N=9010;
int n,m,u[N],v[N];
namespace run
{
	int e,begin[N],next[N],to[N],w[N];
	void Add(int u,int v,int W=0){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; w[e]=W; }
	void add(int u,int v){ Add(u,v,1); Add(v,u,1); }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	int vis[N];
	int dfs(int u,int t)
	{
		if(u==t) return 1;
		if(vis[u]) return 0;
		vis[u]=1;
		fo(i,u) if(w[i]&&dfs(to[i],t)){ w[i]--; w[i^1]++; return 1; }
		return 0;
	}
	int cnt;
	int solve(int x,int y)
	{
		assert((++cnt)<n);
		memset(begin,0,sizeof(begin)); e=1;
		fr(i,1,m) add(u[i],v[i]);
		int ans=0;
		while(1){ memset(vis,0,sizeof(vis)); if(dfs(x,y)) ans++; else return ans; }
	}
}
std::vector<pii> e[N];
void build(std::vector<int> a)
{
	if(a.size()<=1) return ;
	int f=run::solve(a[0],a[1]);
	std::vector<int> b,c;
	e[a[0]].push_back(pii(a[1],f)); e[a[1]].push_back(pii(a[0],f));
	for(auto i:a) (run::vis[i]?b:c).push_back(i);
	build(b); build(c);
}
int ans=0;
void dfs(int u,int lst,int w)
{
	if(lst) ans+=w;
	for(auto i:e[u]) if(i.first!=lst)
		dfs(i.first,u,std::min(w,i.second));
}
int main()
{
	n=read(); m=read();
	fr(i,1,m){ u[i]=read(); v[i]=read(); }
	std::vector<int> a;
	fr(i,1,n) a.push_back(i);
	build(a);
	fr(i,1,n) dfs(i,0,3);
	printf("%d\n",ans/2);
	return 0;
}
