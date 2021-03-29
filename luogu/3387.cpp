/**************************************************************
	File name: 3387.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/9/2018, 9:20:55 AM
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
namespace run
{
	#define N 400010
	int n,begin[N],next[N],to[N],w[N],dfn[N],low[N],u[N],v[N],f[N],t,e,m,nn,s[N],l,is[N],q[N],d[N],r,g[N],ww[N],ans;
	#define fo(i,a) for(int i=begin[u];i;i=next[i])
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
	void dfs(int u)
	{
		dfn[u]=low[u]=++t;
		s[++l]=u;is[u]=1;
		fo(i,u)
			if(!dfn[to[i]])
			{
				dfs(to[i]);
				low[u]=min(low[u],low[to[i]]);
			}
			else if(is[to[i]])
				low[u]=min(low[u],low[to[i]]);
		if(dfn[u]==low[u])
		{
			nn++;
			while(s[l]!=u)
			{
				is[s[l]]=0;
				f[s[l]]=nn;
				l--;
			}
			is[s[l]]=0;
			f[s[l]]=nn;
			l--;
		}
	}
	int main()
	{
		n=read();m=read();
		fr(i,1,n)w[i]=read();
		fr(i,1,m)
		{
			u[i]=read();v[i]=read();
			add(u[i],v[i]);
		}
		fr(i,1,n)if(!dfn[i])dfs(i);
		fr(i,1,n)
		{
			ww[i]=w[i];
			w[i]=0;
		}
		fr(i,1,n)w[f[i]]+=ww[i];
//		fr(i,1,n)printf("%d%c",f[i],i==n?'\n':' ');
		n=nn;e=0;
		fr(i,1,n)begin[i]=0;
//		printf("%d\n",n);
//		fr(i,1,n)printf("%d\n",w[i]);
		fr(i,1,m)
			if(f[u[i]]!=f[v[i]])
			{
				add(f[u[i]],f[v[i]]);
				d[f[v[i]]]++;
			}
		l=1;r=0;
		fr(i,1,n)if(d[i]==0)q[++r]=i;
		while(l<=r)
		{
			int u=q[l];l++;
			g[u]+=w[u];
			ans=max(ans,g[u]);
			fo(i,u)
			{
				d[to[i]]--;
				g[to[i]]=max(g[to[i]],g[u]);
				if(!d[to[i]])
					q[++r]=to[i];
			}
		}
		printf("%d\n",ans);
		return 0;
	}
}
int main()
{
	return run::main();
}