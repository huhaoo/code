/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Thu 12 Nov 2020 09:47:09 PM CST
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
#define pii std::pair<i64,i64>
#define i64 long long
#include<vector>
#include<queue>
const int N=200010;
i64 inf=1ll<<60;
i64 n,t,f[N],v[N],a[N],m,F[N],c[N];
pii w[N];
std::vector<int> e[N];
std::priority_queue<pii> Q;
void dfs(int u)
{
	for(auto v:e[u]) if(v!=f[u])
	{
		f[v]=u; dfs(v);
	}
}
int getf(int u){ return u==F[u]?u:F[u]=getf(F[u]); }
pii operator+(pii a,pii b){ return pii(std::min(a.first,a.second+b.first),a.second+b.second); }
void solve()
{
	n=read(); t=read();
	fr(i,1,n){ f[i]=0; e[i].clear(); }
	fr(i,1,n) v[i]=read();
	fr(i,1,n-1){ int u=read(),v=read(); e[u].push_back(v); e[v].push_back(u); }
	dfs(t); a[m=1]=1; while(a[m]!=t){ a[m+1]=f[a[m]]; m++; }
	a[m+1]=0;
	fr(i,1,m) f[a[i]]=0;
	fr(i,1,n) F[i]=i;
	fr(i,1,n) w[i]=(v[i]<0?pii(v[i],v[i]):pii(0,v[i]));
	fr(i,1,m) w[a[i]]=pii();
	fr(i,1,n) if(w[i].second<=0) c[i]=-inf; else c[i]=0;
	while(!Q.empty()) Q.pop();
	fr(i,1,n) if(f[i]&&w[i].second>0) Q.push(pii(w[i].first,i));
	while(!Q.empty())
	{
		int u=Q.top().second; Q.pop();
		if(F[u]!=u) continue;
		F[u]=getf(f[u]); int v=F[u]; w[v]=w[v]+w[u];
//		printf("- %d %d   %lld\n",u,v,w[u].first);
		if(w[F[u]].second>0)
		{
			c[v]=std::max(c[v],w[v].first);
			if(f[v]) Q.push(pii(w[v].first,v));
		}
	}
//	fr(i,1,n) printf("%lld%c",c[i],i==n?'\n':' ');
	while(!Q.empty()) Q.pop();
	for(auto i:e[1]) if(f[i]==1) Q.push(pii(c[i],i));
	i64 q=1,s=v[1];
	while(q<m)
	{
		while(!Q.empty()&&s+Q.top().first>=0)
		{
			int u=Q.top().second; Q.pop(); s+=v[u];
			for(auto i:e[u]) if(f[i]==u) Q.push(pii(c[i],i));
		}
		q++; s+=v[a[q]];
		for(auto i:e[a[q]]) if(f[i]==a[q]) Q.push(pii(c[i],i));
		if(s<0){ printf("trapped\n"); return ; }
	}
	printf("escaped\n");
}
int main()
{
	fr(T,1,read()) solve();
	return 0;
}
