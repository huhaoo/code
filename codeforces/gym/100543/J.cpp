/***************************************************************
	File name: J.cpp
	Author: huhao
	Create time: Sat 21 Nov 2020 02:55:45 PM CST
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
const int N=1000010;
namespace lct
{
	int s[N][2],r[N],w[N],v[N],f[N];
	void init(int n){ fr(i,1,n) s[i][0]=s[i][1]=r[i]=w[i]=v[i]=f[i]=0; }
	void update(int u){ w[u]=std::max(v[u],std::max(w[s[u][0]],w[s[u][1]])); }
	int isroot(int u){ return s[f[u]][0]!=u&&s[f[u]][1]!=u; }
	int wson(int u){ return s[f[u]][1]==u; }
	void rotate(int u)
	{
		int F=f[u],o=wson(u);
		if(!isroot(F)) s[f[F]][wson(F)]=u;
		f[u]=f[F]; f[F]=u; f[s[u][o^1]]=F; s[F][o]=s[u][o^1]; s[u][o^1]=F;
		update(F); update(u);
	}
	void Rev(int u){ r[u]^=1; std::swap(s[u][0],s[u][1]); }
	void pushdown(int u){ if(r[u]){ Rev(s[u][0]); Rev(s[u][1]); r[u]=0; } }
	void splay(int u)
	{
		static int s[N],t; s[t=1]=u;
		while(!isroot(s[t])){ s[t+1]=f[s[t]]; t++; }
		while(t) pushdown(s[t--]);
		while(!isroot(u))
		{
			if(!isroot(f[u])) rotate(wson(u)==wson(f[u])?f[u]:u);
			rotate(u);
		}
	}
	void access(int u)
	{
		for(int lst=0;u;u=f[u]){ splay(u); s[u][1]=lst; update(u); lst=u; }
	}
	void makeroot(int u){ access(u); splay(u); Rev(u); }
	void link(int u,int v){ makeroot(u); f[u]=v; }
	void cut(int u,int v){ makeroot(u); access(v); splay(v); s[v][0]=f[u]=0; update(v); }
	int findroot(int u)
	{
		access(u); splay(u);
		while(s[u][0]) pushdown(u=s[u][0]);
		splay(u); return u;
	}
	int query(int u)
	{
		if(v[u]==w[u]){ splay(u); return u; }
		if(w[u]==w[s[u][0]]) return query(s[u][0]);
		else return query(s[u][1]);
	}
}
namespace seg
{
	const int M=10000010;
	int s[M][2],t[M],c;
	int clone(int k){ c++; s[c][0]=s[k][0]; s[c][1]=s[k][1]; t[c]=t[k]; return c; }
	int modify(int k,int l,int r,int p,int v)
	{
		k=clone(k); t[k]+=v;
		if(l==r) return k;
		int mid=(l+r)>>1;
		if(p<=mid) s[k][0]=modify(s[k][0],l,mid,p,v);
		else s[k][1]=modify(s[k][1],mid+1,r,p,v);
		return k;
	}
	int query(int k,int l,int r,int p)
	{
		if(!k||l>p) return 0;
		if(r<=p) return t[k];
		int mid=(l+r)>>1;
		return query(s[k][0],l,mid,p)+query(s[k][1],mid+1,r,p);
	}
}
#include<vector>
int n,m,u[N],v[N],w[N],p[N],L[N],R[N],a[N],c,r[N],ans,q;
int main()
{
	fr(T,1,read())
	{
		n=read(); m=read(); lct::init(n+m);
		fr(i,1,m){ u[i]=read(); v[i]=read(); w[i]=read(); p[i]=i; lct::v[i+n]=lct::w[i+n]=w[i]; }
		std::sort(p+1,p+m+1,[&](int u,int v){ return w[u]>w[v]; });
		fr(I,1,m)
		{
			int i=p[I]; R[i]=w[i]; L[i]=0;
			lct::makeroot(u[i]);
			if(lct::findroot(v[i])!=u[i])
			{
				lct::link(u[i],i+n); lct::link(v[i],i+n);
				continue;
			}
			lct::access(v[i]); int p=lct::query(v[i])-n; L[p]=w[i]+1;
			lct::cut(u[p],p+n); lct::cut(v[p],p+n);
			lct::link(u[i],i+n); lct::link(v[i],i+n);
		}
		c=0; fr(i,1,m){ a[++c]=L[i]; a[++c]=R[i]; }
		std::sort(a+1,a+c+1); c=std::unique(a+1,a+c+1)-a-1; seg::c=0;
		std::vector<int> e[N];
		fr(i,1,m) e[std::lower_bound(a+1,a+c+1,L[i])-a].push_back(i);
		fr(i,0,c+2) r[i]=0;
		fr(i,1,c)
		{
			r[i]=r[i-1];
			for(auto j:e[i]) r[i]=seg::modify(r[i],1,c,std::lower_bound(a+1,a+c+1,R[j])-a,w[j]);
		}
		q=read(); ans=0;
		fr(i,1,q)
		{
			int l=read(),r=read(); l-=ans; r-=ans;
			l=std::lower_bound(a+1,a+c+1,l)-a; r=std::upper_bound(a+1,a+c+1,r)-a-1;
			printf("%d\n",ans=seg::query(::r[l],1,c,r)-seg::query(::r[l],1,c,l-1));
		}
	}
	return 0;
}
