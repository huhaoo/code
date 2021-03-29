/***************************************************************
	File name: 4074.cpp
	Author: huhao
	Create time: Wed 23 Oct 2019 11:42:04 AM CST
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
namespace run
{
#define i64 long long
	const int N=200010,W=2048,B=20;
	i64 n,m,q,v[N],w[N],e,begin[N],next[N],to[N],L[N],R[N],cl,c[N],p[N],t[N],l[N],M,Q,ans[N],_l,_r,_t,in[N],T[N],Ans,b[N],f[N][B+5],d[N];
	struct query
	{
		int u,v,t,id,l;
	}a[N];
	int operator<(query a,query b)
	{
		return
			a.u/W!=b.u/W?a.u<b.u:
			a.v/W!=b.v/W?a.v<b.v:
			a.t<b.t;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void dfs(int u,int F)
	{
		int v;
		f[u][0]=F;
		d[u]=d[F]+1;
		L[u]=++cl;
		b[cl]=u;
		fo(i,u)
			if((v=to[i])!=F)
				dfs(v,u);
		R[u]=++cl;
		b[cl]=u;
	}
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
	int lca(int u,int v)
	{
		if(d[u]<d[v])
			swap(u,v);
		fd(i,B,0)
			if(d[f[u][i]]>=d[v])
				u=f[u][i];
		if(u==v)
			return u;
		fd(i,B,0)
			if(f[u][i]!=f[v][i])
			{
				u=f[u][i];
				v=f[v][i];
			}
		return f[u][0];
	}
	int main()
	{
		n=read();
		m=read();
		q=read();
		fr(i,1,m)
			v[i]=read();
		fr(i,1,n)
			w[i]=read();
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			add(u,v);
			add(v,u);
		}
		dfs(1,0);
		fr(j,1,B)
			fr(i,1,n)
				f[i][j]=f[f[i][j-1]][j-1];
		fr(i,1,n)
			c[i]=read();
		fr(i,1,q)
		{
			int opt=read();
			if(opt==0)
			{
				M++;
				p[M]=read();
				t[M]=read();
				l[M]=c[p[M]];
				c[p[M]]=t[M];
			}
			else
			{
				int s=read(),t=read();
				Q++;
				if(L[s]>L[t])
					swap(s,t);
				if(R[s]<L[t])
					a[Q].u=R[s];
				else
					a[Q].u=L[s];
				a[Q].v=L[t];
				a[Q].l=lca(s,t);
				if(a[Q].l==s||a[Q].l==t)
					a[Q].l=0;
//				a[Q].u=read();
//				a[Q].v=read();
				a[Q].id=Q;
				a[Q].t=M;
			}
		}
		sort(a+1,a+Q+1);
		_l=1;
		_r=0;
		_t=M;
		Ans=0;
//		fr(i,1,n)
//			printf("%lld %lld\n",L[i],R[i]);
		fr(i,1,Q)
		{
//			printf("%d %d %d %d\n ",a[i].u,a[i].v,a[i].t,a[i].id);
//			fr(j,1,n)
//				printf("%lld%c",c[j],j==n?'\n':' ');
#define Add(u) Ans+=v[u]*w[++T[u]]
#define Del(u) Ans-=v[u]*w[T[u]--]
			while(_t<a[i].t)
			{
				_t++;
				if((_l<=L[p[_t]]&&L[p[_t]]<=_r)^(_l<=R[p[_t]]&&R[p[_t]]<=_r))
				{
					Del(c[p[_t]]);
					c[p[_t]]=t[_t];
					Add(c[p[_t]]);
				}
				else
					c[p[_t]]=t[_t];
			}
			while(_t>a[i].t)
			{
				if((_l<=L[p[_t]]&&L[p[_t]]<=_r)^(_l<=R[p[_t]]&&R[p[_t]]<=_r))
				{
					Del(c[p[_t]]);
					c[p[_t]]=l[_t];
					Add(c[p[_t]]);
				}
				else
					c[p[_t]]=l[_t];
				_t--;
			}
			while(_l>a[i].u)
			{
				_l--;
				in[b[_l]]^=1;
//				printf("Modify %lld %lld",b[_l],Ans);
				if(in[b[_l]])
					Add(c[b[_l]]);
				else
					Del(c[b[_l]]);
//				printf(" %lld\n",Ans);
			}
			while(_r<a[i].v)
			{
				_r++;
				in[b[_r]]^=1;
//				printf("Modify %lld %lld",b[_r],Ans);
				if(in[b[_r]])
					Add(c[b[_r]]);
				else
					Del(c[b[_r]]);
//				printf(" %lld\n",Ans);
			}
			while(_l<a[i].u)
			{
				in[b[_l]]^=1;
//				printf("Modify %lld %lld",b[_l],Ans);
				if(in[b[_l]])
					Add(c[b[_l]]);
				else
					Del(c[b[_l]]);
//				printf(" %lld\n",Ans);
				_l++;
			}
			while(_r>a[i].v)
			{
				in[b[_r]]^=1;
//				printf("Modify %lld %lld",b[_r],Ans);
				if(in[b[_r]])
					Add(c[b[_r]]);
				else
					Del(c[b[_r]]);
//				printf(" %lld\n",Ans);
				_r--;
			}
			ans[a[i].id]=Ans+(a[i].l?w[T[c[a[i].l]]+1]*v[c[a[i].l]]:0);
		}
		fr(i,1,Q)
			printf("%lld\n",ans[i]);
		return 0;
	}
}
int main()
{
	return run::main();
}
