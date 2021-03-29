/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2020-08-16 19:12:43
****************************************************************/
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#include<queue>
#define Ty i64
#define i64 long long
namespace mcmf
{
	const int N=100010; const Ty inf=1ll<<60;
	i64 h[N],w[N]; Ty c[N],d[N];
	int begin[N],next[N],to[N],e=1;
	void add(int u,int v,i64 W,Ty C){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; w[e]=W; c[e]=C; }
	void Add(int u,int v,i64 w,Ty c){ add(u,v,w,c); add(v,u,0,-c); }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	i64 maxw; Ty minc; int n,vis[N],pre[N];
	typedef std::pair<Ty,int> pii;
	std::priority_queue<pii> q;
	int spfa(int s,int t)
	{
		fr(i,1,n){ d[i]=inf; vis[i]=pre[i]=0; }
		d[s]=0; while(!q.empty()) q.pop(); q.push(pii(0,s));
		while(!q.empty())
		{
			int u=q.top().second; q.pop();
			if(vis[u]) continue;
			vis[u]=1;
			fo(i,u) if(w[i]&&d[u]+h[u]-h[to[i]]+c[i]<d[to[i]])
			{
				d[to[i]]=d[u]+h[u]-h[to[i]]+c[i]; pre[to[i]]=i; q.push(pii(-d[to[i]],to[i]));
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
//			printf("%d %d\n",f,h[t]);
			while(u!=s){ w[pre[u]]-=f; w[pre[u]^1]+=f; u=to[pre[u]^1]; }
		}
	}
}
int n,m,s,t;
int main()
{
	n=read(); m=read();
	fr(i,1,m){ int u=read(),v=read(),w=read(),c=read(); mcmf::Add(u,v,w,c); }
	mcmf::run(n,1,n); printf("%lld %lld\n",mcmf::maxw,mcmf::minc);
	return 0;
}
