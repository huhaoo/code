/***************************************************************
	File name: 4719.cpp
	Author: huhao
	Create time: Sun 08 Sep 2019 07:02:53 PM CST
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
const int M=3;
#define i64 long long
const i64 inf=1ll<<40;
namespace run
{
	struct matrix
	{
		int n,m;
		i64 a[M][M];
		matrix(int _n=0,int _m=0)
		{
			n=_n;
			m=_m;
			memset(a,0,sizeof(a));
		}
		matrix operator*(matrix b)
		{
			if(n==0)
				return b;
			if(b.n==0)
				return *this;
			matrix c;
			c.n=n;
			c.m=b.m;
			fr(i,1,c.n)
				fr(j,1,c.m)
				{
					c.a[i][j]=-inf;
					fr(k,1,m)
						c.a[i][j]=max(c.a[i][j],a[i][k]+b.a[k][j]);
				}
			return c;
		}
		matrix& operator*=(matrix b)
		{
			return *this=*this*b;
		}
	};
	int n,q,begin[N],next[N],to[N],e,w[N],f[N],F[N],s[N],dfn[N],S[N];
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
	i64 g[N][2],V[N];
	namespace segment_tree
	{
		int s[N][2],r[N],c;
		matrix v[N];
		void modify(int &k,int l,int r,int p,matrix V)
		{
			if(!k)
				k=++c;
			if(l==r)
			{
				v[k]=V;
				return;
			}
			int mid=(l+r)>>1;
			if(p<=mid)
				modify(s[k][0],l,mid,p,V);
			else
				modify(s[k][1],mid+1,r,p,V);
			v[k]=v[s[k][0]]*v[s[k][1]];
		}
	}
	void dfs1(int u)
	{
		int v;
		w[u]=1;
		fo(i,u)
			if((v=to[i])!=f[u])
			{
				f[v]=u;
				dfs1(v);
				w[u]+=w[v];
				if(w[v]>w[s[u]])
					s[u]=v;
			}
	}
	matrix zero()
	{
		matrix a=matrix(2,1);
		a.a[2][1]=-inf;
		return a;
	}
	matrix query(int v)
	{
		return segment_tree::v[segment_tree::r[dfn[v]]]*zero();
	}
	void modify(int u)
	{
		matrix a=matrix(2,2);
		a.a[1][1]=g[u][0];
		a.a[1][2]=g[u][0];
		a.a[2][1]=g[u][1];
		a.a[2][2]=-inf;
		segment_tree::modify(segment_tree::r[dfn[F[u]]],dfn[F[u]],dfn[S[u]],dfn[u],a);
	}
	void dfs2(int u,int _f)
	{
		F[u]=_f;
		dfn[u]=++dfn[0];
		if(s[u])
		{
			dfs2(s[u],_f);
			S[u]=S[s[u]];
		}
		else
			S[u]=u;
		g[u][1]=V[u];
		fo(i,u)
		{
			int v=to[i];
			if(v!=f[u]&&v!=s[u])
			{
				dfs2(v,v);
				matrix a=query(v);
				g[u][0]+=max(a.a[1][1],a.a[2][1]);
				g[u][1]+=a.a[1][1];
			}
		}
		modify(u);
	}
	int main()
	{
		n=read();
		q=read();
		fr(i,1,n)
			V[i]=read();
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			add(u,v);
			add(v,u);
		}
		dfs1(1);
		dfs2(1,1);
		while(q--)
		{
			int p=read(),v=read();
			int k=p;
			while(k)
			{
				k=F[k];
				matrix a=query(k);
				g[f[k]][0]-=max(a.a[1][1],a.a[2][1]);
				g[f[k]][1]-=a.a[1][1];
				k=f[k];
			}
			k=p;
			while(k)
			{
				k=f[F[k]];
				if(k)
					modify(k);
			}
			g[p][1]-=V[p];
			V[p]=v;
			g[p][1]+=V[p];
			modify(p);
			k=p;
			while(k)
			{
				k=F[k];
				matrix a=query(k);
				g[f[k]][0]+=max(a.a[1][1],a.a[2][1]);
				g[f[k]][1]+=a.a[1][1];
				k=f[k];
				if(k)
					modify(k);
			}
			matrix a=query(1);
			printf("%lld\n",max(a.a[1][1],a.a[2][1]));
		}
		return 0;
	}
}
int main()
{
	return run::main();
}
