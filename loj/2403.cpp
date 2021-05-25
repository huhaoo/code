/***************************************************************
	File name: 2403.cpp
	Author: huhao
	Create time: Tue 25 May 2021 10:57:44 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define i64 long long
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
#include <queue>
const int N=1000010; const i64 inf=1ll<<60;
namespace mcmf
{
	i64 d[N],h[N],w[N],c[N];
	int begin[N],next[N],to[N],e;
	i64 maxw,minc;
	void init(){ e=1; maxw=minc=0; memset(h,0,sizeof(h)); memset(begin,0,sizeof(begin)); }
	void add(int u,int v,i64 W,i64 C){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; w[e]=W; c[e]=C; }
	void Add(int u,int v,i64 w,i64 c)
	{
//		printf("%d %d %lld,%lld\n",u,v,w,c);
		add(u,v,w,c); add(v,u,0,-c);
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	int n,vis[N],pre[N];
	typedef std::pair<i64,int> pii;
	std::priority_queue<pii> q;
	int spfa(int s,int t)
	{
		fr(i,1,n){ d[i]=inf; vis[i]=pre[i]=0; }
		d[s]=0;
		while(!q.empty()) q.pop();
		q.push(pii(0,s));
		while(!q.empty())
		{
			int u=q.top().second;
			q.pop();
			if(vis[u]) continue;
			vis[u]=1;
			fo(i,u) if(w[i]&&d[u]+h[u]-h[to[i]]+c[i]<d[to[i]])
			{
				d[to[i]]=d[u]+h[u]-h[to[i]]+c[i];
				pre[to[i]]=i;
				q.push(pii(-d[to[i]],to[i]));
			}
		}
		return vis[t];
	}
	void run(int _n,int s,int t)
	{
		n=_n;
		while(spfa(s,t))
		{
			i64 f=inf; int u=t;
			fr(i,1,n) if(d[i]!=inf) h[i]+=d[i];
			while(u!=s){ f=std::min(f,w[pre[u]]); u=to[pre[u]^1]; }
			maxw+=f; minc+=f*h[t]; u=t;
			while(u!=s){ w[pre[u]]-=f; w[pre[u]^1]+=f; u=to[pre[u]^1]; }
		}
	}
}
using mcmf::Add;
int n,a,b;
double p;
int x[N],s[N],t[N],v[N],m;
int c[N];
i64 ans;
int main()
{
	fr(_test_,1,read())
	{
		n=read(); a=read(); b=read(); m=0; ans=0; scanf("%lf",&p);
		fr(i,1,n){ x[i]=read(); s[i]=read(); t[i]=read(); v[++m]=s[i]; v[++m]=t[i]; }
		std::sort(v+1,v+m+1); m=std::unique(v+1,v+m+1)-v-1;
		fr(i,1,m) c[i]=0;
		fr(i,1,n){ s[i]=std::lower_bound(v+1,v+m+1,s[i])-v; t[i]=std::lower_bound(v+1,v+m+1,t[i])-v; fr(j,s[i],t[i]-1) c[j]++; }
		fr(i,1,m-1) if(c[i]>a+b) ans=inf;
		if(ans>0){ printf("impossible\n"); continue; }
		mcmf::init(); int S=(n+1)*m+1,T=S+1;
		Add(S,1+n*m,b,0); Add(n*m+m,T,b,0);
		fr(i,1,m-1) Add(i+n*m,i+1+n*m,a+b-c[i],0);
		fr(i,1,n)
		{
			int P=(x[i]*p+1e-8);
			fr(j,s[i]+1,t[i]) Add(j-1+(i-1)*m,j+(i-1)*m,1,0);
			fr(j,s[i],t[i])
			{
				Add(j+(i-1)*m,j+n*m,1,0/*j==t[i]?0:P*/);
				Add(j+n*m,j+(i-1)*m,1,j==s[i]?x[i]:P);
			}
		}
		mcmf::run(T,S,T); printf("%lld\n",ans+mcmf::minc);
	}
	return 0;
}
