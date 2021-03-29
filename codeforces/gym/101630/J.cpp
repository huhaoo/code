/***************************************************************
	File name: J.cpp
	Author: huhao
	Create time: Mon 23 Nov 2020 09:20:30 PM CST
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
#include<queue>
#define pii std::pair<i64,i64>
const int N=3010;
int n,m,u[N],v[N],w[N],a[N],k;
i64 ans;
std::vector<pii> e[N];
int vis[N]; i64 d[N];
std::priority_queue<pii> q;
i64 solve()
{
	fr(i,1,n){ d[i]=1ll<<60; vis[i]=0; }
	while(!q.empty()) q.pop();
	d[1]=0; q.push({0,1});
	while(!q.empty())
	{
		int u=q.top().second; q.pop();
		if(vis[u]) continue;
		vis[u]=1;
		for(auto v:e[u]) if(d[u]+v.second<d[v.first])
		{
			d[v.first]=d[u]+v.second;
			q.push({-d[v.first],v.first});
		}
	}
	return d[n];
}
int main()
{
	n=read(); m=read(); k=read();
	fr(i,1,m)
	{
		u[i]=read(); v[i]=read(); w[i]=a[i]=read();
		e[u[i]].push_back({v[i],w[i]}); e[v[i]].push_back({u[i],w[i]});
	}
	ans=solve();
	std::sort(a+1,a+m+1);
	fr(i,1,m)
	{
		fr(j,1,n) e[j].clear();
		fr(j,1,m)
		{
			e[u[j]].push_back({v[j],std::max(0,w[j]-a[i])}); e[v[j]].push_back({u[j],std::max(0,w[j]-a[i])});
		}
//		printf("%d %lld\n",a[i],solve());
		ans=std::min(ans,solve()+(i64)k*a[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
