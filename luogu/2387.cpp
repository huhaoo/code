/***************************************************************
	File name: 2387.cpp
	Author: huhao
	Create time: Mon 09 Sep 2019 07:18:34 PM CST
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
const int N=400010,inf=1<<29;
namespace lct
{
	int s[N][2],R[N],m[N],w[N],f[N],a[N][2];
	void update(int k)
	{
		m[k]=max(w[k],max(m[s[k][0]],m[s[k][1]]));
	}
	void reverse(int k)
	{
		if(R[k])
		{
			R[s[k][0]]^=1;
			R[s[k][1]]^=1;
			R[k]=R[0]=0;
			swap(s[k][0],s[k][1]);
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
	void rotate(int k)
	{
		int F=f[k],o=wson(k);
		if(!isroot(F))
			s[f[F]][wson(F)]=k;
		f[k]=f[F];
		f[F]=k;
		f[s[k][o^1]]=F;
		s[F][o]=s[k][o^1];
		s[k][o^1]=F;
		update(F);
		update(k);
	}
	int S[N];
	void splay(int k)
	{
		int x=k;
		S[S[0]=1]=x;
		while(!isroot(x))
		{
			x=f[x];
			S[++S[0]]=x;
		}
		while(S[0])
			reverse(S[S[0]--]);
		while(!isroot(k))
		{
			if(!isroot(f[k]))
				rotate(wson(k)==wson(f[k])?f[k]:k);
			rotate(k);
		}
	}
	void access(int k)
	{
		int lst=0;
		while(k)
		{
			splay(k);
			s[k][1]=lst;
			update(k);
			lst=k;
			k=f[k];
		}
	}
	void makeroot(int k)
	{
		access(k);
		splay(k);
		R[k]^=1;
	}
	int findroot(int k)
	{
		access(k);
		splay(k);
		reverse(k);
		while(s[k][0])
		{
			k=s[k][0];
			reverse(k);
		}
		splay(k);
		return k;
	}
	void link(int u,int v)
	{
		makeroot(v);
		f[v]=u;
	}
	void cut(int u,int v)
	{
		makeroot(u);
		access(v);
		splay(v);
		f[u]=s[v][0]=0;
		update(v);
	}
	int findmax(int k)
	{
		if(w[k]>=m[s[k][0]]&&w[k]>=m[s[k][1]])
		{
			splay(k);
			return k;
		}
		else if(m[s[k][0]]>m[s[k][1]])
			return findmax(s[k][0]);
		else
			return findmax(s[k][1]);
	}
	void Link(int u,int v,int W)
	{
		makeroot(u);
		if(findroot(v)==u)
		{
//			printf("%d %d %d\n",u,v,W);
			access(v);
			splay(v);
			int k=findmax(v);
			splay(k);
//			printf("%d %d\n",k,w[k]);
			if(w[k]<=W)
				return;
			int x=a[k][0],y=a[k][1];
//			printf("%d %d %d\n",k,x,y);
			cut(k,x);
			cut(k,y);
		}
		link(u,v);
	}
	void print(int k)
	{
		if(!k)
			return;
		print(s[k][0]);
		printf("%d ",k);
		print(s[k][1]);
	}
	int query(int u,int v)
	{
		makeroot(u);
		if(findroot(v)!=u)
			return inf;
		access(v);
		splay(v);
//		putchar(' ');
//		print(v);
//		putchar(10);
		return m[v];
	}
}
int n,m,c,ans;
struct edge
{
	int u,v,a,b;
	edge(int U=0,int V=0,int A=0,int B=0)
	{
		u=U;
		v=V;
		a=A;
		b=B;
	}
}e[N];
int cmp(edge a,edge b)
{
	return a.a<b.a;
}
int main()
{
	n=read();
	m=read();
	ans=inf;
	fr(i,1,m)
	{
		int u=read(),v=read(),a=read(),b=read();
		e[i]=edge(u,v,a,b);
	}
	sort(e+1,e+m+1,cmp);
	c=n;
	fr(i,1,m)
	{
		c++;
		lct::m[c]=lct::w[c]=e[i].b;
		lct::a[c][0]=e[i].u;
		lct::a[c][1]=e[i].v;
		lct::Link(e[i].u,c,e[i].b);
		lct::Link(e[i].v,c,e[i].b);
//		printf("%d\n",lct::query(1,n));
		ans=min(ans,lct::query(1,n)+e[i].a);
	}
	printf("%d\n",ans!=inf?ans:-1);
	return 0;
}
