#pragma GCC optimize("O2,Ofast,inline,unroll-all-loops,-ffast-math")
/***************************************************************
	File name: 3823.cpp
	Author: huhao
	Create time: Wed 11 Sep 2019 09:02:52 PM CST
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
int inputs(char *s)
{
	int l=0;
	*s=getchar();
	while(*s<'0'||*s>'9')
		*s=getchar();
	while(*s>='0'&&*s<='9')
	{
		l++;
		s++;
		*s=getchar();
	}
	*s=0;
	return l;
}
#define i64 unsigned long long
const i64 seed=19260817;
struct bs
{
	i64 a1,a2,a3;
	bs()
	{
		a1=a2=a3=0;
	}
	bs operator<<(int k)
	{
		bs a;
		a.a1=(a1<<k)|(a2>>(64-k));
		a.a2=(a2<<k)|(a3>>(64-k));
		a.a3=a3<<k;
		return a;
	}
	bs operator|(i64 k)
	{
		bs a=*this;
		a.a3|=k;
		return a;
	}
	bs last(i64 k)
	{
		bs a=*this;
		if(k<=64)
		{
			a.a1=a.a2=0;
			a.a3&=(-1ull)>>(64-k);
		}
		else if(k<=128)
		{
			a.a1=0;
			a.a2&=(-1ull)>>(128-k);
		}
		else
			a.a1&=(-1ull)>>(192-k);
		return a;
	}
	bs& operator=(i64 k)
	{
		a1=a2=0;
		a3=k;
		return *this;
	}
	i64 hash()
	{
		return (a1*seed+a2)*seed+a3;
	}
	int empty()
	{
		return (!a1)&&(!a2)&&(!a3);
	}
	int operator==(bs a)
	{
		return a1==a.a1&&a2==a.a2&&a3==a.a3;
	}
};
namespace hash
{
	const int N=19491001,M=30000000;
	int begin[N+5],next[M],v[M],e;
	bs to[M];
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void add(bs a,int V)
	{
		i64 H=a.hash()%N;
//		printf("add %llu %d\n",H,V);
		fo(i,H)
			if(to[i]==a)
			{
				v[i]+=V;
				return;
			}
		e++;
		v[e]=V;
		to[e]=a;
		next[e]=begin[H];
		begin[H]=e;
	}
	int query(bs a)
	{
		i64 H=a.hash()%N;
		fo(i,H)
			if(to[i]==a)
				return v[i];
		return 0;
	}
}
const int N=200010,K=50,S=10000010,mod=998244353;
int n,q,a[N],l[N],r[N];
bs f[N][K+2];
char s[S];
void update(int k,int s=1)
{
	fr(i,s,K-1)
		if(!f[k][i].empty())
		{
			hash::add(f[k][i],-1);
			f[k][i]=0;
		}
		else
			break;
	fr(i,s,K-1)
		if(!f[r[k]][i-1].empty())
		{
			f[k][i]=(f[r[k]][i-1]<<3)|a[k];
			hash::add(f[k][i],1);
		}
		else 
			break;
}
int main()
{
	n=read();
	q=read();
	fr(i,1,n)
	{
		a[i]=read();
		f[i][0]=a[i];
		hash::add(f[i][0],1);
	}
	while(q--)
	{
//		printf("-------------------------------\n");
		int opt=read();
		if(opt==1)
		{
			int u=read(),v=read();
			r[u]=v;
			l[v]=u;
/*			while(u)
			{
				update(u);
				u=l[u];
			}*/
			fr(i,0,K-1)
			{
				if(u)
					update(u,i+1);
				u=l[u];
			}
		}
		else if(opt==2)
		{
			int u=read(),v;
			v=r[u];
			r[u]=l[v]=0;
/*			while(u)
			{
				update(u);
				u=l[u];
			}*/
			fr(i,0,K-1)
			{
				if(u)
					update(u,i+1);
				u=l[u];
			}
		}
		else
		{
			int L=inputs(s+1),k=read();
			bs a;
			i64 ans=1;
			fr(i,1,k-1)
				a=a<<3|(s[L-i+1]-'0');
			fr(i,k,L)
			{
				a=a<<3|(s[L-i+1]-'0');
				ans=ans*hash::query(a.last(k*3))%mod;
//				printf("query %llu: %d\n",a.last(k*3).hash(),hash::query(a.last(k*3)));
			}
			printf("%llu\n",ans);
		}
	}
	return 0;
}
