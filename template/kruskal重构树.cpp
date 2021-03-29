/**************************************************************
	File name: 4768.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/11/2019, 9:38:27 AM
	Example:
	- https://www.luogu.org/problemnew/show/P4768
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
#include<queue>
namespace run
{
	#define N 800010
	#define l 20
	#define inf ((int)((1ll<<31)-1))
	int n,m,begin[N],next[N],to[N],e,w[N],p[N],d[N],g[N],t,f[N][l+5],a[N][l+5],v[N],s,o,ans,ms;
	void add(int u,int v,int W)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=W;
	}
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	struct road
	{
		int u,v,w,a;
		road(int U=0,int V=0,int W=0,int A=0)
		{
			u=U;
			v=V;
			w=W;
			a=A;
		}
	}r[N];
	struct dij
	{
		int u,d;
		dij(int U=0,int D=0)
		{
			u=U;
			d=D;
		}
	};
	bool operator<(dij a,dij b)
	{
		return a.d>b.d;
	}
	int get(int u)
	{
		return u==p[u]?u:(p[u]=get(p[u]));
	}
	int cmp(road a,road b)
	{
		return a.a>b.a;
	}
	priority_queue<dij>q;
	int main()
	{
		n=read();
		m=read();
		e=0;
		fr(i,1,n)
			begin[i]=0;
		fr(i,1,m)
		{
			r[i].u=read();
			r[i].v=read();
			r[i].w=read();
			r[i].a=read();
		}
		fr(i,1,n*2-1)
			p[i]=i;
		sort(r+1,r+m+1,cmp);
		t=n;
		fr(i,1,m)
		{
			int fu=get(r[i].u),fv=get(r[i].v);
			if(fu!=fv)
			{
				t++;
				p[fu]=t;
				p[fv]=t;
				f[fu][0]=t;
				f[fv][0]=t;
				a[fu][0]=r[i].a;
				a[fv][0]=r[i].a;
			}
		}
		fr(j,1,l)
			fr(i,1,t)
			{
				f[i][j]=f[f[i][j-1]][j-1];
				a[i][j]=min(a[i][j-1],a[f[i][j-1]][j-1]);
			}
		fr(i,1,m)
		{
			add(r[i].u,r[i].v,r[i].w);
			add(r[i].v,r[i].u,r[i].w);
		}
		while(!q.empty())
			q.pop();
		fr(i,2,t)
			d[i]=inf;
		fr(i,1,n)
			v[i]=0;
		d[1]=0;
		q.push(dij(1,0));
		while(!q.empty())
		{
			int u=q.top().u;
			q.pop();
			if(v[u])
				continue;
			v[u]=1;
			fo(i,u)
				if(d[u]+w[i]<d[to[i]])
				{
					d[to[i]]=d[u]+w[i];
					q.push(dij(to[i],d[to[i]]));
				}
		}
		fr(i,1,t-1)
			d[f[i][0]]=min(d[f[i][0]],d[i]);
		s=read();
		o=read();
		ms=read();
		ans=0;
		while(s--)
		{
			int v=read(),p=read();
			v=(v+o*ans-1)%n+1;
			p=(p+o*ans)%(ms+1);
			fd(i,l,0)
				if(f[v][i]&&a[v][i]>p)
					v=f[v][i];
			printf("%d\n",ans=d[v]);
		}
		return 0;
	}
}
int main()
{
	fr(t,1,read())
		run::main();
	return 0;
}