/**************************************************************
	File name: 1600.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/2/2018, 3:13:00 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#include<vector>
namespace run
{
	#define N 900010
	#define M 20
	int n,m,begin[N],next[N],to[N],ans[N],a[N],h[N],w[N],e,f[N][M+10];
	vector<int>t1[N],t2[N];
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void dfs1(int u)
	{
		int v;
		fo(i,u)if(f[u][0]!=(v=to[i]))
		{
			f[v][0]=u;h[v]=h[u]+1;
			dfs1(v);
		}
	}
	int lca(int u,int v)
	{
		if(h[u]<h[v])swap(u,v);
		fd(i,M,0)if(h[f[u][i]]>=h[v])u=f[u][i];
		fd(i,M,0)if(f[u][i]!=f[v][i])u=f[u][i],v=f[v][i];
		return u==v?u:f[u][0];
	}
	void dfs2(int u)
	{
		int v;ans[u]-=a[h[u]+w[u]];
		fr(i,0,t1[u].size()-1)
			if(t1[u][i]>0)a[t1[u][i]]++;
			else a[-t1[u][i]]--;
		fo(i,u)if(f[u][0]!=(v=to[i]))dfs2(v);
		ans[u]+=a[h[u]+w[u]];
	}
	void dfs3(int u)
	{
		int v;ans[u]-=a[h[u]-w[u]+n];
		fr(i,0,t2[u].size()-1)
			if(t2[u][i]>0)a[t2[u][i]]++;
			else a[-t2[u][i]]--;
		fo(i,u)if(f[u][0]!=(v=to[i]))dfs3(v);
		ans[u]+=a[h[u]-w[u]+n];
	}
	int main()
	{
		n=read();
		m=read();
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			add(u,v);add(v,u);
		}
		fr(i,1,n)w[i]=read();
		h[1]=1;dfs1(1);
		fr(i,1,M)fr(j,1,n)f[j][i]=f[f[j][i-1]][i-1];
		fr(i,1,m)
		{
			int u=read(),v=read(),l;l=lca(u,v);
			t1[u].push_back(h[u]);
			t1[l].push_back(-h[u]);
			t2[f[l][0]].push_back(-(h[l]*2-h[u]+n));
			t2[v].push_back(h[l]*2-h[u]+n);
		}
		dfs2(1);dfs3(1);
		fr(i,1,n)printf("%d%c",ans[i],i==n?'\n':' ');
		return 0;
	}
}
int main(){return run::main();}