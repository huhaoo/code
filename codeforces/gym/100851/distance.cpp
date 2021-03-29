/***************************************************************
	File name: distance.cpp
	Author: huhao
	Create time: Mon 16 Nov 2020 11:31:50 AM CST
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
#define pii std::pair<int,int>
#include<map>
#include<vector>
const int N=100010,L=18;
namespace solve
{
	int d[N]; std::vector<int> e[N];
	int vis[N],q[N],l,r;
	void add(int u,int v){ e[u].push_back(v); e[v].push_back(u); }
	void solve(std::vector<int> v,std::vector<pii> E,int s)
	{
		for(auto i:v){ d[i]=N; e[i].clear(); vis[i]=0; }
		for(auto i:E) add(i.first,i.second);
		fr(i,0,v.size()-1) add(v[i],v[i==end_i?0:i+1]);
		d[s]=0; q[l=r=1]=s; vis[s]=1;
		while(l<=r)
		{
			int u=q[l++];
			for(auto i:e[u]) if(!vis[i])
			{
				d[i]=d[u]+1; q[++r]=i; vis[i]=1;
			}
		}
	}
}
std::map<int,int> D[N];
int n,m;
int f[N][L+2],d[N]; pii a[N];
void build(std::vector<int> v,std::vector<pii> e,int _f)
{
/*	for(auto i:v) printf("%d ",i); putchar(10);
	for(auto i:e) printf("(%d,%d) ",i.first,i.second); putchar(10);
	putchar(10); fflush(stdout);*/
	if(v.size()==2) return ;
	if(v.size()==3)
	{
		for(auto i:v) if(!f[i][0]){ d[i]=d[_f]+1; f[i][0]=_f; }
		return ;
	}
	static int id[N];
	fr(i,0,v.size()-1) id[v[i]]=i;
	pii mi=e[0]; int n=v.size();
	for(auto i:e) if(std::abs(n/2-std::abs(id[i.first]-id[i.second]))<std::abs(n/2-std::abs(id[mi.first]-id[mi.second]))) mi=i;
	solve::solve(v,e,mi.first); for(auto i:v) D[mi.first][i]=solve::d[i];
	solve::solve(v,e,mi.second); for(auto i:v) D[mi.second][i]=solve::d[i];
	std::vector<int> v1,v2; std::vector<pii> e1,e2;
	if(id[mi.first]>id[mi.second]) std::swap(mi.first,mi.second);
	fr(i,id[mi.first],id[mi.second]) v1.push_back(v[i]);
	fr(i,id[mi.second],n-1) v2.push_back(v[i]);
	fr(i,0,id[mi.first]) v2.push_back(v[i]);
#define in(a,b,c) ((b<a)&&(a<c))
	for(auto i:e)
	{
		if(i==mi||pii(i.second,i.first)==mi) continue;
		((in(id[i.first],id[mi.first],id[mi.second])||in(id[i.second],id[mi.first],id[mi.second]))?e1:e2).push_back(i);
	}
	m++; f[m][0]=_f; d[m]=d[_f]+1; a[m]=mi;
	if(!f[mi.first][0]){ f[mi.first][0]=m; d[mi.first]=d[m]+1; }
	if(!f[mi.second][0]){ f[mi.second][0]=m; d[mi.second]=d[m]+1; }
	int k=m; build(v1,e1,k); build(v2,e2,k);
}
int lca(int u,int v)
{
	if(d[u]<d[v]) std::swap(u,v);
	fd(i,L,0) if(d[f[u][i]]>=d[v]) u=f[u][i];
//	printf("%d %d   %d %d\n",u,v,d[u],d[v]);
//	fd(i,L,0) printf("%d %d\n",f[u][i],f[v][i]);
	if(u==v) return u;
	fd(i,L,0) if(f[u][i]!=f[v][i]){ u=f[u][i]; v=f[v][i]; }
	return f[u][0];
}
int main()
{
	freopen("distance.in","r",stdin); freopen("distance.out","w",stdout);
	std::vector<pii> e; std::vector<int> v;
	n=read(); m=n; fr(i,1,n) v.push_back(i);
	fr(i,1,n-3){ int u=read(),v=read(); e.push_back({u,v}); }
	build(v,e,0);
//	fr(i,1,n) fr(j,1,n) printf("%d%c",D[i][j],j==n?'\n':' ');
//	fr(i,1,m) printf("%d %d   %d %d\n",f[i][0],d[i],a[i].first,a[i].second);
	fr(j,1,L) fr(i,1,m) f[i][j]=f[f[i][j-1]][j-1];
	fr(q,1,read())
	{
		int u=read(),v=read(),l=lca(u,v);
//		printf("%d %d  %d  %d %d\n",u,v,l,a[l].first,a[l].second);
		if(u==v){ printf("0\n"); continue; }
		printf("%d\n",std::min(D[a[l].first][u]+D[a[l].first][v],D[a[l].second][u]+D[a[l].second][v]));
	}
	return 0;
}
