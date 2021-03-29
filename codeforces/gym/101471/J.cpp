/***************************************************************
	File name: J.cpp
	Author: huhao
	Create time: Fri 23 Oct 2020 10:53:05 AM CST
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
const int N=1000010;
const double eps=1e-8,inf=1e20;
namespace dinic
{
	int n,begin[N],next[N],to[N],cur[N],e,s,t;
	double d[N],w[N];
	void add(int u,int v,double W){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; w[e]=W; }
	void Add(int u,int v,double w){ add(u,v,w); add(v,u,0); }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
#define Fo(i,a) for(int &i=cur[a];i;i=next[i])
	void init(){ e=1; memset(begin,0,sizeof(begin)); }
	int bfs()
	{
		fr(i,1,n){ d[i]=n+1; cur[i]=begin[i]; }
		static int q[N],l,r;
		d[t]=0; q[l=r=1]=t;
		while(l<=r)
		{
			int u=q[l++];
			fo(i,u) if(w[i^1]>eps&&d[to[i]]>d[u]+1)
			{
				d[to[i]]=d[u]+1;  q[++r]=to[i];
			}
		}
		return d[s]<=n;
	}
	double dfs(int u,double F)
	{
		if(u==t) return F;
		Fo(i,u)
			if(w[i]>eps&&d[to[i]]==d[u]-1)
			{
				double f=dfs(to[i],std::min(F,w[i]));
				if(f>eps){ w[i]-=f; w[i^1]+=f; return f; }
			}
		return 0;
	}
	double dinic(int _n,int S,int T)
	{
		double ans=0,f; s=S; t=T; n=_n;
		while(bfs()) while((f=dfs(s,inf))>eps) ans+=f;
		return ans;
	}
}
int n,m; double t,a;
int u[N],v[N]; double w[N];
double w1[N],w2[N];
int main()
{
	n=read(); m=read(); scanf("%lf%lf",&t,&a);
	fr(i,1,m){ u[i]=read(); v[i]=read(); scanf("%lf",&w[i]); }
	dinic::init(); fr(i,1,m){ dinic::add(u[i],v[i],w[i]); dinic::add(v[i],u[i],w[i]); }
	double f3=dinic::dinic(n,2,3),f4=dinic::dinic(n,1,3);
	dinic::init(); fr(i,1,m){ dinic::add(u[i],v[i],w[i]); dinic::add(v[i],u[i],w[i]); }
	double f1=dinic::dinic(n,1,3),f2=dinic::dinic(n,2,3);
	double f0=f1+f2;
	double l=f4,r=f1;
	while(r-l>eps)
	{
		double p=(r-l)/3,p1=l+p,p2=r-p;
		if(pow(p1,a)*pow(f0-p1,1-a)<pow(p2,a)*pow(f0-p2,1-a)) l=p1;
		else r=p2;
	}
	dinic::init(); fr(i,1,m){ dinic::add(u[i],v[i],w[i]); dinic::add(v[i],u[i],w[i]); }
	dinic::Add(n+1,1,l); dinic::Add(n+1,2,f0-l); dinic::dinic(n+1,n+1,3);
	fr(i,1,m) w1[i]=w[i]-dinic::w[i*2];
	dinic::init();
	fr(i,1,m) if(w1[i]>0) dinic::Add(u[i],v[i],w1[i]); else dinic::Add(v[i],u[i],-w1[i]);
	dinic::Add(n+1,1,l); dinic::dinic(n+1,n+1,3);
	fr(i,1,m) w2[i]=(w1[i]>0?1:-1)*dinic::w[i*2+1];
	fr(i,1,m) printf("%.10lf %.10lf\n",w2[i]/t,w1[i]-w2[i]);
	printf("%.10lf\n",pow(l/t,a)*pow(f0-l,1-a));
	return 0;
}
