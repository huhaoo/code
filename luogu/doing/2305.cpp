/***************************************************************
	File name: 2305.cpp
	Author: huhao
	Create time: Wed 12 Jun 2019 04:08:13 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define i64 long long
#define fr(i,a,b) for(i64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(i64 i=(a),end_##i=(b);i>=end_##i;i--)
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
namespace run
{
	const i64 N=400010,L=18,M=10000010,inf=1ll<<60;
	i64 n,e,begin[N],next[N],to[N],f[N][L+5],w[N],l[N],d[N],b[N],p[N],q[N],r[L+5][N],pre[L+5][N],ans[N],dfn[N],del[N];
	i64 s[M][2],a[M],cnt;
	void add(i64 u,i64 v,i64 _w)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=_w;
	}
	i64 clone(i64 p)
	{
		cnt++;
		a[cnt]=a[p];
		b[cnt]=b[p];
		s[cnt][0]=s[p][0];
		s[cnt][1]=s[p][1];
		return cnt;
	}
	void split(i64 k,i64 v,i64 &l,i64 &r)
	{
		if(!k)
		{
			l=r=0;
			return;
		}
		if(a[k]<=v)
	}
	void ins(i64 k,i64 x)
	{
		i64 l,r;
		split(k,x,l,r);
		if(l)
		{
		}
	}
	void build(i64 x,i64 y)
	{
		i64 l=((x-1)<<y)+1,r=x<<y,p=0,_p=1;
		fr(i,l,r)
			if(!del[i])
			{
				i64 k=clone(p);
				pre[k]=_p;
				ins(k,i);
				_p=p=k;
			}
		r[x][y]=p;
	}
#define fo(i,a) for(i64 i=begin[a];i;i=next[i])
	void dfs(i64 u)
	{
		dfn[u]=++dfn[0];
		if(u!=1)
		{
			i64 _f=u;
			fd(i,L,0)
				if(d[u]-d[f[_f][i]]<=l[u])
					_f=f[_f][i];
			ans[i]=inf;
			i64 x=_f,y=0,xx=dfn[u]-1,yy=0;
			while(r[x][y])
			{
				if(x&1)
				{
					x=(x+1)/2;
					y++;
				}
				else
				{
					ans[i]=query(r[x][y],p[u]);
					x=x/2+1;
					y++;
				}
			}
			while(r[xx][yy]&&(xx!=x||yy!=y))
			{
				if(x&1)
				{
					ans[i]=query(r[xx][yy],p[u]);
					x=x/2;
					y++;
				}
				else
				{
					x=x/2;
					y++;
				}
			}
		}
		i64 x=dfn[u],y=0;
		build(x,0);
		while(!(x&1))
		{
			x=x/2;
			y++;
			build(x,y);
		}
		fo(i,u)
			if(to[i]!=f[u][0])
				dfs(to[i]);
		x=dfn[u];
		y=0;
		while(r[x][y])
		{
			r[x][y]=pre[r[x][y]];
			x=(x+1)>>1;
			y++;
		}
		del(u)=1;
	}
	int main()
	{
		b[cnt=1]=-inf;
		pre[1]=1;
		n=read();
		read();
		fr(i,2,n)
		{
			f[i][0]=read();
			i64 w=read();
			p[i]=read();
			q[i]=read();
			l[i]=read();
			add(i,f[i][0],w);
			add(f[i][0],i,w);
			d[i]=d[f[i][0]]+w;
		}
		fr(j,1,L)
			fr(i,1,n)
				f[i][j]=f[f[i][j-1]][j-1];
		dfs(1);
		return 0;
	}
}
int main()
{
	return run::main();
}
