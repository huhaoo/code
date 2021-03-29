/**************************************************************
	File name: 2-sat.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/3/2018, 2:17:01 PM
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
	#define N 8000010
	int n,e,m,u[N],v[N],begin[N],next[N],to[N],s[N],top,f[N],nn,dfn[N],low[N],k,d[N],l,r,q[N],rank[N],is[N];
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void add(int uu,int vv)
	{
		e++;
		u[e]=uu;v[e]=vv;
		next[e]=begin[uu];
		begin[uu]=e;
		to[e]=vv;
	}
	void tarjan(int u)
	{
		int v;low[u]=dfn[u]=++k;s[++top]=u;is[u]=1;
		fo(i,u)if(dfn[v=to[i]])
		{
			if(is[v])low[u]=min(low[u],dfn[v]);
		}
		else
		{
			tarjan(v);low[u]=min(low[u],low[v]);
		}
//		printf("%d %d %d\n",u,dfn[u],low[u]);
		if(dfn[u]==low[u])
		{
			nn++;
			while(s[top+1]!=u){f[s[top]]=nn;is[s[top]]=0;top--;}
		}
	}
	int main()
	{
		n=read();
		m=read();
		fr(i,1,m)
		{
			int u=read()*2+read(),v=read()*2+read();
			add(u^1,v);add(v^1,u);
		}
		fr(i,2,2*n+1)if(!dfn[i])tarjan(i);
//		fr(i,2,2*n+1)printf("%d%c",f[i],i==2*n+1?'\n':' ');
		fr(i,1,n)if(f[i*2]==f[i*2+1]){printf("IMPOSSIBLE");return 0;}
		e=0;fr(i,1,n)begin[i]=0;
		fr(i,1,e)if(f[u[i]]!=f[v[i]]){add(f[v[i]],f[u[i]]);d[u[i]]++;}
		l=1;r=0;
		fr(i,1,nn)if(!d[i])q[++r]=i;
		while(l<=r)
		{
			int t=q[l],v;rank[t]=l;l++;
			fo(i,l)
			{
				d[v=to[i]]--;
				if(!d[v])q[++r]=v;
			}
		}
		printf("POSSIBLE\n");
		fr(i,1,n)printf("%d%c",rank[f[i<<1]]>rank[f[i<<1|1]],i==n?'\n':' ');
		return 0;
	}
}
int main(){return run::main();}