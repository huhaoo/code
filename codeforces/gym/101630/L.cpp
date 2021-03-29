/***************************************************************
	File name: L.cpp
	Author: huhao
	Create time: Mon 30 Nov 2020 04:26:19 PM CST
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
#include<vector>
const int N=1<<18|10;
int n,m,dfn[N],Dfn,w[N],d[N],s[N],f[N],F[N];
int a[N],b[N],l[N],p[N];
int t[N],v[N],c;
std::vector<int> e[N];
void dfs(int u)
{
	d[u]=d[f[u]]+1; w[u]=1;
	for(auto v:e[u]) if(v!=f[u]){ f[v]=u; dfs(v); w[u]+=w[v]; if(w[v]>w[s[u]]) s[u]=v; }
}
void Dfs(int u,int _f)
{
	dfn[u]=++Dfn; F[u]=_f; if(s[u]) Dfs(s[u],_f);
	for(auto v:e[u]) if(v!=f[u]&&v!=s[u]) Dfs(v,v);
}
int lca(int u,int v)
{
	while(F[u]!=F[v])
	{
		if(d[F[u]]<d[F[v]]) std::swap(u,v);
		u=f[F[u]];
	}
	return d[u]<d[v]?u:v;
}
void Tag(int u,int w){ t[u]=v[u]=w; }
void pushdown(int u){ if(t[u]!=-1){ Tag(u<<1,t[u]); Tag(u<<1|1,t[u]); } }
void update(int u){ if(t[u<<1]==t[u<<1|1]) t[u]=t[u<<1]; else t[u]=-1; }
void modify(int k,int l,int r,int L,int R,int op)
{
//	if(k==1&&L<=R) printf("%d %d  %d\n",L,R,op);
	if(l>R||L>r) return ;
	if(L<=l&&r<=R)
	{
		if(t[k]==-1||(c!=-1&&t[k]!=c)){ printf("No\n"); exit(0); }
		c=t[k]; Tag(k,op); return ;
	}
	int mid=(l+r)>>1; pushdown(k);
	modify(k<<1,l,mid,L,R,op); modify(k<<1|1,mid+1,r,L,R,op); update(k);
}
void modify(int u,int v,int op)
{
	while(F[u]!=F[v])
	{
		modify(1,1,n,dfn[F[u]],dfn[u],op);
		u=f[F[u]];
	}
	modify(1,1,n,dfn[v]+1,dfn[u],op);
}
int main()
{
	n=read(); m=read();
	fr(i,1,n-1)
	{
		int u=read(),v=read();
		e[u].push_back(v); e[v].push_back(u);
	}
	dfs(1); Dfs(1,1);
	fr(i,1,m){ a[i]=read(); b[i]=read(); l[i]=lca(a[i],b[i]); p[i]=i; }
	std::sort(p+1,p+m+1,[&](int x,int y){ return d[a[x]]+d[b[x]]-2*d[l[x]]>d[a[y]]+d[b[y]]-2*d[l[y]]; });
//	fr(i,1,m) printf("%d%c",d[a[p[i]]]+d[b[p[i]]]-2*d[l[p[i]]],i==m?'\n':' ');
//	fr(i,1,n) printf("%d%c",d[i],i==n?'\n':' ');
	fr(I,1,m)
	{
		int i=p[I]; c=-1; //printf("%d %d   %d\n",a[i],b[i],l[i]);
		modify(a[i],l[i],i); modify(b[i],f[l[i]],i);
	}
	printf("Yes\n");
	return 0;
}
