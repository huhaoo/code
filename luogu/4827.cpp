/***************************************************************
	File name: 4827.cpp
	Author: huhao
	Create time: Tue 06 Aug 2019 07:21:28 PM CST
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
	const int N=100010,K=200,mod=10007;
	int n,k,begin[N],next[N],to[N],e,f[N][K],s[K][K],F[N],w[N],g[K],fac[N];
	void add(int u,int v)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void dfs(int u)
	{
		int v;
		w[u]=1;
		fo(i,u)
			if((v=to[i])!=F[u])
			{
				F[v]=u;
				dfs(v);
				fr(j,1,k)
					f[u][j]=(f[u][j]+f[v][j-1]+f[v][j])%mod;
				w[u]+=w[v];
			}
		f[u][0]=w[u];
	}
	void calc(int u)
	{
		fr(i,1,k)
			g[i]=(f[u][i]+f[u][i-1])%mod;
		g[0]=f[u][0];
		fr(i,0,k)
			g[i]=(f[F[u]][i]-g[i]+mod)%mod;
		fd(i,k,1)
			g[i]=(g[i]+g[i-1])%mod;
		fr(i,0,k)
			f[u][i]=(f[u][i]+g[i])%mod;
		fo(i,u)
			if(to[i]!=F[u])
				calc(to[i]);
	}
	int main()
	{
		n=read();
		k=read();
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			add(u,v);
			add(v,u);
		}
		s[1][1]=1;
		fr(i,2,k)
			fr(j,1,i)
			{
				s[i][j]=(s[i-1][j-1]+j*s[i-1][j])%mod;
			}
		fac[0]=1;
		fr(i,1,k)
			fac[i]=fac[i-1]*i%mod;
		dfs(1);
		fo(i,1)
			calc(to[i]);
		fr(i,1,n)
		{
			int ans=0;
			fr(j,0,k)
				ans=(ans+fac[j]*s[k][j]%mod*f[i][j])%mod;
			printf("%d\n",ans);
		}
		return 0;
	}
}
int main()
{
	return run::main();
}
