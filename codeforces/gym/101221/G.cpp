/***************************************************************
	File name: G.cpp
	Author: huhao
	Create time: Mon 04 Jan 2021 11:02:17 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
const int N=410,M=N*N;
int n,m;
struct E{ int u,v,w; } e[M];
int ans;
std::vector<int> t[N];
int id[N],f[N],c,d[N];
int dfs(int u,int c)
{
	if(id[u]) return id[u]==c;
	id[u]=c;
	for(auto v:t[u]) if(!dfs(v,c^1)) return 0;
	return 1;
}
void getf(int u)
{
	if(f[u]==u) return ;
	getf(f[u]); d[u]^=d[f[u]]; f[u]=f[f[u]];
}
int merge(int u,int v)
{
	getf(u); getf(v);
	if(f[u]==f[v]) return d[u]!=d[v];
	f[f[v]]=u; d[f[v]]^=1; return 1;
}
int Id[N],dfn[N],low[N],Dfn,_id;
void tarjan(int u)
{
	static int s[N],S,vis[N];
	dfn[u]=low[u]=++Dfn; s[++S]=u; vis[u]=1;
	for(auto v:t[u])
		if(!dfn[v])
		{
			tarjan(v); low[u]=std::min(low[u],low[v]);
		}
		else if(vis[v]) low[u]=std::min(low[u],dfn[v]);
	if(dfn[u]==low[u])
	{
		_id++;
		while(s[S]!=u){ vis[s[S]]=0; Id[s[S]]=_id; S--; }
		vis[u]=0; Id[u]=_id; S--;
	}
}
bool check(int w1,int w2)
{
	if(w1>w2) return 0;
	fr(i,1,n) t[i].clear();
	fr(i,1,m) if(e[i].w>w2){ t[e[i].u].push_back(e[i].v); t[e[i].v].push_back(e[i].u); }
	c=1;
	fr(j,1,n) id[j]=0;
	fr(j,1,n) if(!id[j]){ c+=2; if(!dfs(j,c)) return 0; }
//	printf("%d %d  %d\n",w1,w2,c); fr(i,1,n) printf("%d%c",id[i],i==n?'\n':' ');
	fr(i,1,c) t[i].clear();
	fr(i,1,m) if(e[i].w<=w2&&e[i].w>w1)
	{
		int u=id[e[i].u],v=id[e[i].v];
		t[u].push_back(v^1); t[v].push_back(u^1);
//		printf("%d %d\n",u,v);
	}
	Dfn=_id=0; fr(i,2,c) dfn[i]=0;
	fr(i,2,c) if(!dfn[i]) tarjan(i);
//	fr(i,2,c) printf("%d%c",Id[i],i==c?'\n':' ');; putchar(10);
	fr(i,2,c) if(Id[i]==Id[i^1]) return 0;
	return 1;
}
int main()
{
	n=read();
	fr(i,1,n) fr(j,i+1,n){ m++; e[m].u=i; e[m].v=j; e[m].w=read(); }
	std::sort(e+1,e+m+1,[](E a,E b){ return a.w<b.w; });
	ans=e[m].w;
	for(int i=0,j=m;i<=m;i++) while(j>=0&&check(e[i].w,e[j].w)){ ans=std::min(ans,e[i].w+e[j].w); j--; }
	printf("%d\n",ans);
	return 0;
}
