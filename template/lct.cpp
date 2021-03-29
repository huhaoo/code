/***************************************************************
	File name: lct.cpp
	Author: huhao
	Create time: Thu 18 Jun 2020 05:08:59 PM CST
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
const int N=100010;
namespace lct
{
	int s[N][2],f[N],r[N],v[N],w[N];
	int isroot(int u){ return s[f[u]][0]!=u&&s[f[u]][1]!=u; }
	int wson(int u){ return s[f[u]][1]==u; }
	void Rev(int u){ r[u]^=1; std::swap(s[u][0],s[u][1]); }
	void pushdown(int u){ if(r[u]){ Rev(s[u][0]); Rev(s[u][1]); r[u]=0; } }
	void update(int u){ w[u]=w[s[u][0]]^w[s[u][1]]^v[u]; }
	void rotate(int u)
	{
		int o=wson(u),_f=f[u];
		if(!isroot(_f)) s[f[_f]][wson(_f)]=u;
		f[u]=f[_f]; f[_f]=u; f[s[u][o^1]]=_f; s[_f][o]=s[u][o^1]; s[u][o^1]=_f;
		update(_f); update(u);
	}
	void splay(int u)
	{
		static int s[N],t; s[t=1]=u; int v=u;
		while(!isroot(v)) s[++t]=(v=f[v]);
		while(t) pushdown(s[t--]);
		while(!isroot(u))
		{
			if(!isroot(f[u])) rotate(wson(u)==wson(f[u])?f[u]:u);
			rotate(u);
		}
	}
	void access(int u)
	{
		for(int lst=0;u;lst=u,u=f[u]){ splay(u); s[u][1]=lst; update(u); }
	}
	void makeroot(int u){ access(u); splay(u); Rev(u); }
	int findroot(int u)
	{
		access(u); splay(u);
		while(s[u][0]){ u=s[u][0]; pushdown(u); }
		splay(u); return u;
	}
	void link(int u,int v)
	{
		makeroot(u);
		if(findroot(v)==u) return ;
		f[u]=v;
	}
	void cut(int u,int v)
	{
		makeroot(u);
		access(v); splay(v);
		if(f[u]==v&&!s[u][1]){ f[u]=s[v][0]=0; update(v); }
	}
	void modify(int u,int c){ splay(u); v[u]=c; update(u); }
	int query(int u,int v){ makeroot(u); access(v); splay(v); return w[v]; }
}
int main()
{
	int n=read(),q=read();
	fr(i,1,n) lct::modify(i,read());
	while(q--)
	{
		int opt=read(),u=read(),v=read();
		if(opt==1)      lct::link(u,v);
		else if(opt==2) lct::cut(u,v);
		else if(opt==0) printf("%d\n",lct::query(u,v));
		else            lct::modify(u,v);
//		fr(i,1,n) printf("%d %d %d  %d\n",lct::f[i],lct::s[i][0],lct::s[i][1],lct::w[i]);
	}
	return 0;
}
