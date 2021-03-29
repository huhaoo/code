/**************************************************************
	File name: 3233.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 12/22/2018, 9:13:03 PM
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
	#define N 600010
	#define b 20
	#define B (b+5)
	#define inf (1<<20)
	int begin[N],next[N<<1],to[N<<1],w[N],f[N][B],n,q,e,h[N],d[N],c[N],cl;
	#define fo(i,a) for(int i=begin[u];i;i=next[i])
	int s[N],t,bl[N],f2[N],a[N],vi[N],tv,ts[N],l,r,dg[N],ans[N],p[N];
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
	void dfs(int u)
	{
		if(cl>n)return;
		c[u]=++cl;
		w[u]=1;
		int v;
		fo(i,u)
			if(f[u][0]!=(v=to[i]))
			{
				f[v][0]=u;
				d[v]=d[u]+1;
				dfs(v);
				w[u]+=w[v];
			}
	}
	int lca(int u,int v)
	{
		if(d[u]<d[v])swap(u,v);
		fd(i,b,0)
			if(d[f[u][i]]>=d[v])u=f[u][i];
		fd(i,b,0)
			if(f[u][i]!=f[v][i])
			{
				u=f[u][i];
				v=f[v][i];
			}
		return u==v?u:f[u][0];
	}
	int kthf(int u,int k)
	{
		fd(i,b,0)
			if((k>>i)&1)
				u=f[u][i];
		return u;
	}
	int cmp(int x,int y)
	{
		return c[x]<c[y];
	}
	int dis(int u,int v)
	{
		if(u==0||v==0)return inf;
		int l=lca(u,v);
		return d[u]+d[v]-2*d[l];
	}
	int cmpd(int u,int v,int f)
	{
		int uu,vv;
		if((uu=dis(u,f))==(vv=dis(v,f)))
			return u<v;
		return uu<vv;
	}
	int main()
	{
		n=read();
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			add(u,v);
			add(v,u);
		}
		d[1]=1;
		dfs(1);
		fr(j,1,b)
			fr(i,1,n)
				f[i][j]=f[f[i][j-1]][j-1];
		q=read();
		while(q--)
		{
			int m=read();
			fr(i,1,m)
				p[i]=a[i]=read();
			sort(a+1,a+m+1,cmp);
//			fr(i,1,m)printf("%d%c",a[i],i==m?'\n':' ');
			vi[tv=1]=1;
			s[t=1]=1;
			fr(i,1,m)
			{
				int f,l=0;
				if(a[i]==1)continue;
				while(lca(a[i],s[t])!=s[t])
				{
//					printf("   %d %d %d\n",a[i],s[t],lca(a[i],s[t]));
					l=s[t];
					t--;
				}
				if(l)
					f=lca(a[i],l);
				else
					f=s[t];
//				printf(" %d %d %d\n",a[i],s[t],f);
//				printf("  ");
//				fr(i,1,t)printf("%d%c",s[i],i==t?'\n':' ');
				if(f==s[t])
				{
					f2[a[i]]=s[t];
					vi[++tv]=a[i];
					s[++t]=a[i];
				}
				else
				{
					f2[f]=s[t];
					f2[a[i]]=f;
					f2[s[t+1]]=f;
					vi[++tv]=f;
					s[++t]=f;
					vi[++tv]=a[i];
					s[++t]=a[i];
				}
			}
//			fr(i,1,tv)printf(" %d %d\n",vi[i],f2[vi[i]]);
			fr(i,1,tv)
				bl[vi[i]]=dg[vi[i]]=ans[vi[i]]=0;
			fr(i,2,tv)
				dg[f2[vi[i]]]++;
			l=1;r=0;
			fr(i,1,tv)
				if(!dg[vi[i]])
					ts[++r]=vi[i];
			while(l<=r)
			{
				int u=ts[l];l++;
				dg[f2[u]]--;
				if(!dg[f2[u]])
					ts[++r]=f2[u];
			}
			fr(i,1,m)
				bl[a[i]]=a[i];
			fr(i,1,tv-1)
				if(cmpd(bl[ts[i]],bl[f2[ts[i]]],f2[ts[i]]))
					bl[f2[ts[i]]]=bl[ts[i]];
			fd(i,tv-1,1)
				if(cmpd(bl[f2[ts[i]]],bl[ts[i]],ts[i]))
					bl[ts[i]]=bl[f2[ts[i]]];
			fr(i,1,tv)
				ans[bl[ts[i]]]=w[ts[i]];
			fr(i,1,tv-1)
				if(bl[ts[i]]!=bl[f2[ts[i]]])
				{
					int u1,u2,d1,d2,d3;
					int mid;
					u1=bl[ts[i]];
					u2=bl[f2[ts[i]]];
					d1=dis(u1,ts[i]);
					d2=dis(u2,f2[ts[i]]);
					d3=dis(ts[i],f2[ts[i]]);
					d1-=d2;
					if(d1>=d3)
						mid=ts[i];
					if(-d1>=d3)
						mid=kthf(ts[i],d3-1);
					else
					{
						d3+=d1;
						mid=kthf(ts[i],d3/2-d1-(d3%2==0&&u1>u2));
					}
					ans[u1]+=w[mid]-w[ts[i]];
					ans[u2]-=w[mid];
				}
			fr(i,1,m)
				printf("%d%c",ans[p[i]],i==m?'\n':' ');
		}
		return 0;
	}
}
int main()
{
	return run::main();
}