/***************************************************************
	File name: 带花树.cpp
	Author: huhao
	Create time: Sat 15 Aug 2020 12:10:30 PM CST
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
const int N=510;
int a[N][N],p[N],n,m,vis[N],q[N],l,r,f[N],Vis[N],T,ans,pre[N];
int getf(int u){ return u==f[u]?u:f[u]=getf(f[u]); }
void flower(int u,int v,int l)
{
	while(getf(u)!=l)
	{
		pre[u]=v; v=p[u];
		if(f[u]==u) f[u]=l;
		if(f[v]==v) f[v]=l;
		if(vis[v]==0){ vis[v]=1; q[++r]=v; }
		u=pre[v];
	}
}
int lca(int u,int v)
{
	T++;
	while(1)
	{
		u=getf(u);
		if(Vis[u]==T) return u;
		Vis[u]=T; u=pre[p[u]]; if(v) std::swap(u,v);
	}
}
int solve(int x)
{
	fr(i,1,n){ vis[i]=-1; f[i]=i; pre[i]=0; }
	q[l=r=1]=x; vis[x]=1;
	while(l<=r)
	{
		int u=q[l++];
		fr(v,1,n) if(a[u][v])
		{
			if(vis[v]==-1)
			{
				if(!p[v])
				{
					while(u&&v){ int l=p[u]; p[u]=v; p[v]=u; v=l; u=pre[v]; }
					return 1;
				}
				vis[v]=0; vis[p[v]]=1; pre[v]=u; q[++r]=p[v];
			}
			else if(vis[v]==1)
			{
				int l=lca(u,v); flower(u,v,l); flower(v,u,l);
			}
		}
	}
	return 0;
}
int main()
{
	n=read(); m=read();
	fr(i,1,m){ int u=read(),v=read(); a[u][v]=a[v][u]=1; if(!p[u]&&!p[v]){ p[u]=v; p[v]=u; ans++; } }
	fr(i,1,n) if(!p[i]) ans+=solve(i);
	printf("%d\n",ans);
	fr(i,1,n) printf("%d%c",p[i],i==n?'\n':' ');
	return 0;
}
