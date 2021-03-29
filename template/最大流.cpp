/***************************************************************
	File name: 最大流.cpp
	Author: huhao
	Create time: Fri 19 Jun 2020 10:13:19 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=20010;
const i64 inf=1ll<<50;
namespace dinic
{
	int n,begin[N],next[N],to[N],cur[N],e=1,s,t,d[N];
	i64 w[N];
	void add(int u,int v,i64 W){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; w[e]=W; }
	void Add(int u,int v,i64 w){ add(u,v,w); add(v,u,0); }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
#define Fo(i,a) for(int &i=cur[a];i;i=next[i])
	int bfs()
	{
		fr(i,1,n){ d[i]=n+1; cur[i]=begin[i]; }
		static int q[N],l,r;
		d[t]=0; q[l=r=1]=t;
		while(l<=r)
		{
			int u=q[l++];
			fo(i,u) if(w[i^1]&&d[to[i]]>d[u]+1)
			{
				d[to[i]]=d[u]+1;  q[++r]=to[i];
			}
		}
		return d[s]<=n;
	}
	i64 dfs(int u,i64 F)
	{
		if(u==t) return F;
		Fo(i,u)
			if(w[i]&&d[to[i]]==d[u]-1)
			{
				i64 f=dfs(to[i],std::min(F,w[i]));
				if(f){ w[i]-=f; w[i^1]+=f; return f; }
			}
		return 0;
	}
	i64 dinic(int _n,int S,int T)
	{
		i64 ans=0,f; s=S; t=T; n=_n;
		while(bfs()) while((f=dfs(s,inf))) ans+=f;
		return ans;
	}
}
int n,m,s,t;
int main()
{
	n=read(); m=read(); s=read(); t=read();
	fr(i,1,m){ int u=read(),v=read(),w=read(); dinic::Add(u,v,w); }
	printf("%lld\n",dinic::dinic(n,s,t));
	return 0;
}
