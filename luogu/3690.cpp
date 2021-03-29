/***************************************************************
	File name: 3690.cpp
	Author: huhao
	Create time: Fri 12 Jul 2019 02:01:20 PM CST
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
const int N=300010;
int n,q,v[N],w[N],s[N][2],f[N],rev[N];
void update(int k)
{
	w[k]=v[k]^w[s[k][0]]^w[s[k][1]];
}
void reverse(int k)
{
	if(rev[k])
	{
		swap(s[k][0],s[k][1]);
		rev[s[k][0]]^=1;
		rev[s[k][1]]^=1;
		rev[k]=rev[0]=0;
	}
}
int isroot(int k)
{
	return s[f[k]][0]!=k&&s[f[k]][1]!=k;
}
int wson(int k)
{
	return s[f[k]][1]==k;
}
void rotate(int x)
{
	int _f=f[x],o=wson(x);
	if(!isroot(_f))
		s[f[_f]][wson(_f)]=x;
	f[x]=f[_f];
	f[_f]=x;
	f[s[x][o^1]]=_f;
	s[_f][o]=s[x][o^1];
	s[x][o^1]=_f;
	f[0]=0;
	update(_f);
	update(x);
}
int R[N];
void splay(int x)
{
	int k=x;
	R[0]=0;
	while(!isroot(k))
	{
		R[++R[0]]=k;
		k=f[k];
	}
	R[++R[0]]=k;
	while(R[0])
	{
		reverse(R[R[0]]);
		R[0]--;
	}
	while(!isroot(x))
	{
		if(!isroot(f[x]))
			rotate(wson(x)==wson(f[x])?f[x]:x);
		rotate(x);
	}
}
void access(int x)
{
	int k=0;
	while(x)
	{
		splay(x);
		s[x][1]=k;
		k=x;
		update(x);
		x=f[x];
	}
}
int findroot(int x)
{
	access(x);
	splay(x);
	reverse(x);
	while(s[x][0])
	{
		x=s[x][0];
		reverse(x);
	}
	splay(x);
	return x;
}
void makeroot(int x)
{
	access(x);
	splay(x);
	rev[x]^=1;
}
void modfiy(int x,int _v)
{
	splay(x);
	v[x]=_v;
	update(x);
}
void link(int u,int v)
{
	makeroot(u);
	if(findroot(v)==u)
		return;
	f[u]=v;
}
void cut(int u,int v)
{
	makeroot(u);
	if(findroot(v)!=u)
		return;
	access(v);
	splay(v);
	reverse(u);
	if(s[v][0]!=u&&s[u][1])
		return;
	s[v][0]=f[u]=0;
	update(v);
}
int query(int u,int v)
{
	makeroot(u);
	access(v);
	splay(v);
	return w[v];
}
int main()
{
	n=read();
	q=read();
	fr(i,1,n)
		w[i]=v[i]=read();
	while(q--)
	{
		int opt=read(),_u=read(),_v=read();
		if(opt==0)
		{
			printf("%d\n",query(_u,_v));
		}
		else if(opt==1)
		{
			link(_u,_v);
		}
		else if(opt==2)
		{
			cut(_u,_v);
		}
		else
		{
			modfiy(_u,_v);
		}
	}
	return 0;
}
