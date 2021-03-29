/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Fri 29 Jan 2021 11:15:06 AM CST
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
const int N=200010;
int n,p,P;
std::vector<int> e[N],E[N];
int d[N],D[N],t[N],F[N];
void dfs(int u){ for(auto v:e[u]) if(!d[v]){ d[v]=d[u]+1; dfs(v); } }
void Dfs(int u){ for(auto v:E[u]) if(!D[v]){ F[v]=u; D[v]=D[u]+1; Dfs(v); } }
int ans;
void _dfs(int u,int f=0)
{
	if(d[u]>=D[u]) return ;
//	printf("%d %d %d  %d\n",u,d[u],D[u],t[u]);
	ans=std::max(ans,D[u]); if(t[u]) ans=n+1;
	for(auto v:e[u]) if(v!=f) _dfs(v,u);
}
bool check(int u,int v)
{
	int _d=2;
	while(u!=v)
	{
		if(D[u]<D[v]) std::swap(u,v);
		u=F[u]; _d--; if(_d<0) return 1;
	}
	return 0;
}
int main()
{
	n=read(); p=read(); P=read();
	fr(i,1,n-1){ int u=read(),v=read(); e[u].push_back(v); e[v].push_back(u); }
	fr(i,1,n-1){ int u=read(),v=read(); E[u].push_back(v); E[v].push_back(u); }
	d[p]=D[P]=1; dfs(p); Dfs(P);
//	fr(i,1,n) printf(" %d %d\n",d[i],D[i]);
	fr(i,1,n-1) for(auto j:e[i]) if(check(i,j)) t[i]=1;
	_dfs(p);
	printf("%d\n",ans==n+1?-1:(ans-1)*2);
	return 0;
}
