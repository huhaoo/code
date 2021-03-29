/***************************************************************
	File name: 2081.cpp
	Author: huhao
	Create time: Sun 09 Jun 2019 10:41:06 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
const int N=200010;
int n,m;
namespace run1
{
	int begin[N],next[N],to[N],e,w[N],F[N],d[N];
	double f[N],g[N],ans;
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void add(int u,int v,int _w)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=_w;
	}
	void dfs1(int u)
	{
		int v;
		fo(i,u)
			if((v=to[i])!=F[u])
			{
				F[v]=u;
				dfs1(v);
				f[u]+=w[i]+f[v];
			}
		if(u==1)
			f[u]/=d[u];
		else
			if(d[u]!=1)
				f[u]/=d[u]-1;
			else
				f[u]=0;
	}
	void dfs2(int u)
	{
		int v;
		fo(i,u)
			if((v=to[i])!=F[u])
			{
				if(d[u]==1)
					g[v]=(f[v]*(d[v]-1)+w[i])/d[v];
				else
					g[v]=(f[v]*(d[v]-1)+w[i]+(g[u]*d[u]-f[v]-w[i])/(d[u]-1))/d[v];
				dfs2(v);
			}
	}
	int main()
	{
		fr(i,1,n-1)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w);
			add(v,u,w);
			d[u]++;
			d[v]++;
		}
		dfs1(1);
		g[1]=f[1];
		dfs2(1);
		fr(i,1,n)
			ans+=g[i]/n;
		printf("%.5lf\n",ans);
		return 0;
	}
#undef fo
}
namespace run2
{
	int begin[N],next[N],to[N],w[N],e,id[N],d[N],s[N],t,is[N],vis[N],pos[N],m,F[N],l[N];
	double f[N],g[N],h[N],ans;
	void add(int u,int v,int _w)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=_w;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void dfs1(int u)
	{
		int v;
		vis[u]=1;
		is[u]=1;
		s[++t]=u;
		fo(i,u)
			if(vis[v=to[i]])
			{
				if(is[v]&&s[t-1]!=v)
				{
					fd(j,t,1)
					{
						m++;
						pos[s[j]]=m;
						id[m]=s[j];
						if(s[j]==v)
							break;
					}
				}
			}
			else
				dfs1(v);
		t--;
		is[u]=0;
	}
	void dfs2(int u)
	{
		fo(i,u)
			if(to[i]!=F[u]&&!pos[to[i]])
			{
				F[to[i]]=u;
				dfs2(to[i]);
				f[u]+=f[to[i]]+w[i];
			}
		if(pos[u])
		{
			if(d[u]!=2)
				f[u]/=d[u]-2;
			else
				f[u]=0;
		}
		else
		{
			if(d[u]!=1)
				f[u]/=d[u]-1;
			else
				f[u]=0;
		}
	}
	void dfs3(int u)
	{
		fo(i,u)
			if(to[i]!=F[u]&&!pos[to[i]])
			{
				int v=to[i];
				g[v]=(f[v]*(d[v]-1)+w[i]+(g[u]*d[u]-w[i]-f[v])/(d[u]-1))/d[v];
				dfs3(v);
			}
	}
	int main()
	{
		fr(i,1,n)
		{
			int u=read(),v=read(),w=read();
			add(u,v,w);
			add(v,u,w);
			d[u]++;
			d[v]++;
		}
		m=0;
		dfs1(1);
		fr(i,1,m)
			dfs2(id[i]);
		fr(i,1,m)
			fo(j,id[i])
				if(to[j]==id[i%m+1])
					l[i]=w[j];
		fr(i,1,m)
		{
			double sp=1.;
			int sl=l[i];
			for(int j=i%m+1;;j=j%m+1)
				if(j%m+1==i)
				{
					h[i]+=sp*(f[id[j]]+sl);
					break;
				}
				else
				{
					h[i]+=sp*(d[id[j]]-2)/(d[id[j]]-1)*(f[id[j]]+sl);
					sp/=d[id[j]]-1;
					sl+=l[j];
				}
			sp=1.;
			sl=l[i==1?m:i-1];
			for(int j=i==1?m:i-1;;j=j==1?m:j-1)
				if((j==1?m:j-1)==i)
				{
					h[i]+=sp*(f[id[j]]+sl);
					break;
				}
				else
				{
					h[i]+=sp*(d[id[j]]-2)/(d[id[j]]-1)*(f[id[j]]+sl);
					sp/=d[id[j]]-1;
					sl+=l[j==1?m:j-1];
				}
		}
		fr(i,1,m)
		{
			int u=id[i];
			g[u]=(f[u]*(d[u]-2)+h[i])/d[u];
			dfs3(u);
		}
		fr(i,1,n)
			ans+=g[i]/n;
		printf("%.5lf\n",ans);
		return 0;
	}
#undef fo
}
int main()
{
	n=read();
	m=read();
	if(m==n-1)
		return run1::main();
	else if(m==n)
		return run2::main();
	return 0;
}
