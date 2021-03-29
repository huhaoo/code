/***************************************************************
	File name: C.cpp
	Author: huhao
	Create time: Sun 17 Jan 2021 10:22:19 AM CST
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
#include<map>
#include<queue>
const int N=250010;
const i64 inf=1ll<<40;
std::vector<i64> e[N];
std::map<i64,i64> E[N];
i64 n,w[N],d[N],W[N],mx[N];
void dfs(int u,int f)
{
	W[u]=1;
	for(auto v:e[u]) if(v!=f){ d[v]=d[u]+E[u][v]; dfs(v,u); W[u]+=W[v]; if(W[v]>W[mx[u]]) mx[u]=v; }
}
std::priority_queue<i64,std::vector<i64>,std::greater<i64> > q1[30],q2[30];
i64 ans;
void Dfs(int u,int f,int l=0)
{
	if(mx[u]) Dfs(mx[u],u,l);
	for(auto v:e[u]) if(v!=f&&v!=mx[u])
	{
		Dfs(v,u,l+1);
		while(!q1[l+1].empty()){ q1[l].push(q1[l+1].top()); q1[l+1].pop(); }
		while(!q2[l+1].empty()){ q2[l].push(q2[l+1].top()); q2[l+1].pop(); }
	}
	if(w[u]>0) while(w[u]--){ ans+=inf; q1[l].push(-inf+d[u]); }
	else while(w[u]++) q2[l].push(d[u]);
	while(!q1[l].empty()&&!q2[l].empty()&&q1[l].top()+q2[l].top()-2*d[u]<0)
	{
		i64 x=q1[l].top(),y=q2[l].top(); q1[l].pop(); q2[l].pop();
		ans+=x+y-2*d[u]; q1[l].push(-y+d[u]+d[u]); q2[l].push(-x+d[u]+d[u]);
	}
}
int main()
{
	n=read();
	fr(i,1,n-1){ int u=read(),v=read(),w=read(); e[u].push_back(v); e[v].push_back(u); E[u][v]=E[v][u]=w; }
	fr(i,1,n){ w[i]-=read(); w[i]+=read(); }
	dfs(1,0); Dfs(1,0,0);
	printf("%lld\n",ans);
	return 0;
}
