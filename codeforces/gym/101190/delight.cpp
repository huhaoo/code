/***************************************************************
	File name: delight.cpp
	Author: huhao
	Create time: Thu 12 Nov 2020 07:16:51 PM CST
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
#include<queue>
#define Ty i64
#define i64 long long
namespace mcmf
{
	const int N=100010; const Ty inf=1ll<<60;
	i64 w[N]; Ty c[N],d[N];
	int begin[N],next[N],to[N],e=1;
	void add(int u,int v,i64 W,Ty C)
	{
//		if(W) printf("%d %d  %lld,%lld\n",u,v,W,C);
		e++; next[e]=begin[u]; begin[u]=e; to[e]=v; w[e]=W; c[e]=C;
	}
	void Add(int u,int v,i64 w,Ty c){ add(u,v,w,c); add(v,u,0,-c); }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	i64 maxw; Ty minc; int n,vis[N],pre[N];
	std::queue<int> q;
	int spfa(int s,int t)
	{
		fr(i,1,n){ d[i]=inf; vis[i]=pre[i]=0; }
		d[s]=0; while(!q.empty()) q.pop(); q.push(s);
		while(!q.empty())
		{
			int u=q.front(); q.pop();
//			fprintf(stderr,"%d %lld\n",u,d[u]);
			vis[u]=0;
			fo(i,u) if(w[i]&&d[u]+c[i]<d[to[i]])
			{
				d[to[i]]=d[u]+c[i]; pre[to[i]]=i;
				if(!vis[to[i]]){ q.push(to[i]); vis[to[i]]=1; }
			}
		}
		return d[t]<inf/2;
	}
	void run(int _n,int s,int t,int op=0)
	{
		n=_n;
		while(spfa(s,t))
		{
			i64 f=op?1:inf; int u=t;
//			fr(i,1,n) fprintf(stderr,"%d%c",to[pre[i]^1],i==n?'\n':' ');
			while(u!=s){ f=std::min(f,w[pre[u]]); u=to[pre[u]^1]; }
			maxw+=f; minc+=f*d[t]; u=t;
//			fprintf(stderr,"%d %d\n",f,d[t]);
//			while(u!=s){ fprintf(stderr,"(%d,%d)\n",to[pre[u]^1],u); u=to[pre[u]^1]; }
			u=t;
			while(u!=s){ w[pre[u]]-=f; w[pre[u]^1]+=f; u=to[pre[u]^1]; }
			if(op) break;
		}
	}
}
const int N=10010,inf=123456789;
int n,k,l,r,m;
i64 a[N],ans;
int s,t,S,T;
int main()
{
	freopen("delight.in","r",stdin); freopen("delight.out","w",stdout);
	n=read(); k=read(); l=read(); r=k-read();
	fr(i,1,n) ans+=(a[i]=read());
	fr(i,1,n) a[i]=read()-a[i];
	m=n-k; s=m+1; t=m+2; S=m+3; T=m+4;
	using mcmf::add; using mcmf::Add; using mcmf::run;
	static int e[N];
	fr(i,1,n)
	{
		int u=i-k,v=i;
		if(u<=0) u=s; if(v>m) v=t;
		Add(u,v,1,-a[i]);
		e[i]=mcmf::e;
//		putchar('\n');
	}
	fr(i,0,m)
	{
		int u=i,v=i+1;
		if(u<=0) u=s; if(v>m) v=t;
		add(u,v,r-l,0); add(v,u,0,0);
	}
	int _e=mcmf::e;
	Add(S,s,k-l,0); Add(t,T,k-l,0); fflush(stdout);
	run(m+4,S,T);
//	printf("%lld %lld\n",mcmf::minc,mcmf::maxw);
	printf("%lld\n",ans-mcmf::minc);
	fr(i,1,n) putchar(mcmf::w[e[i]]?'E':'S');
	return 0;
}
