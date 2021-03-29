/**************************************************************
	File name: 1967.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/4/2018, 2:15:31 PM
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
	#define N 100010
	#define B 20
	int n,m,e,begin[N],next[N],to[N],w[N],f[N],h[N],ff[N][B+10],mi[N][B+10];
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	struct road
	{
		int u,v,w;
		road(){u=v=w=0;}
	}r[N];
	int cmp(road a,road b){return a.w>b.w;}
	int getf(int x){return f[x]=x==f[x]?x:getf(f[x]);}
	void add(int u,int v,int ww)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=ww;
	}
	void dfs(int u)
	{
		int v;
		fo(i,u)if(ff[u][0]!=(v=to[i]))
		{
			h[v]=h[u]+1;ff[v][0]=u;mi[v][0]=w[i];
			dfs(v);
		}
	}
	int lca(int u,int v)
	{
		if(h[u]<h[v])swap(u,v);
		fd(i,B,0)if(h[ff[u][i]]>=h[v])u=ff[u][i];
		fd(i,B,0)if(ff[u][i]!=ff[v][i])u=ff[u][i],v=ff[v][i];
		return u==v?u:ff[u][0];
	}
	int main()
	{
		n=read();m=read();
		fr(i,1,m)r[i].u=read(),r[i].v=read(),r[i].w=read();
		sort(r+1,r+m+1,cmp);
		fr(i,1,n)f[i]=i;
		fr(i,1,m)if(getf(r[i].u)!=getf(r[i].v))
		{
			add(r[i].u,r[i].v,r[i].w);add(r[i].v,r[i].u,r[i].w);
			f[getf(r[i].u)]=getf(r[i].v);
		}
		fr(i,1,n)if(!h[i]){h[i]=1;dfs(i);}
		fr(i,1,B)fr(j,1,n)ff[j][i]=ff[ff[j][i-1]][i-1],mi[j][i]=min(mi[j][i-1],mi[ff[j][i-1]][i-1]);
		int q=read();
		while(q--)
		{
			int u=read(),v=read();
			if(getf(u)!=getf(v)){printf("-1\n");continue;}
			int l=lca(u,v),ans=(1<<29);
			fd(i,B,0)if(h[ff[u][i]]>=h[l])ans=min(ans,mi[u][i]),u=ff[u][i];
			u=v;
			fd(i,B,0)if(h[ff[u][i]]>=h[l])ans=min(ans,mi[u][i]),u=ff[u][i];
			printf("%d\n",ans);
		}
		return 0;
	}
}
int main(){return run::main();}