/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Mon 25 Jan 2021 09:45:21 AM CST
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
#define i64 long long
#define pii std::pair<i64,i64>
#include<vector>
const int N=1<<18|10;
i64 n,s[N][2],d[N],l,r,m;
std::vector<pii> f[N];
void dp(int u)
{
	f[u].clear();
	if(!s[u][0]){ f[u]={{d[u],d[u]}}; return ; }
	dp(s[u][0]); dp(s[u][1]);
	auto a=f[s[u][0]],b=f[s[u][1]];
	if(a.size()>b.size()) std::swap(a,b);
	if(a.empty()) return ;
	for(auto i:a) if(i.first+b[0].first-2*d[u]<=m) f[u].push_back({i.second,(--std::lower_bound(b.begin(),b.end(),pii{m+2*d[u]-i.first+1,0}))->second});
	auto g=f[u];
	for(auto i:f[u]) g.push_back({i.second,i.first});
	std::sort(g.begin(),g.end()); f[u].clear();
	fr(i,0,g.size()-1) if(i==0||g[i].second<(--f[u].end())->second) f[u].push_back(g[i]);
//	printf(" %d %lld   %lld %lld   %lld %lld\n",u,d[u],s[u][0],s[u][1],d[s[u][0]]-d[u],d[s[u][1]]-d[u]);
//	for(auto i:f[u]) printf("%lld %lld\n",i.first,i.second);
}
int main()
{
	n=read();
	fr(i,2,n)
	{
		int f=read(),w=read();
		if(s[f][0]) s[f][1]=i; else s[f][0]=i;
		d[i]=d[f]+w;
	}
	l=0; r=1ll<<40;
	while(l<r)
	{
		m=(l+r)>>1; dp(1);
		if(!f[1].empty()) r=m;
		else l=m+1;
	}
	printf("%lld\n",l);
	return 0;
}
