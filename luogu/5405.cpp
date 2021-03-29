/***************************************************************
	File name: 5405.cpp
	Author: huhao
	Create time: Tue 21 May 2019 10:08:32 AM CST
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
	const int N=4010,mod=998244353;
	long long n,inv[N],begin[N],next[N],to[N],w[N],e,a[N][5],f[N][N],_f[N],ans,s[N];
	void add(int u,int v,int _w)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=_w;
	}
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	long long power(long long a,long long b,long long p)
	{
		long long r=1;
		while(b)
		{
			if(b&1)
				r=r*a%p;
			a=a*a%p;
			b>>=1;
		}
		return r;
	}
	void dfs(int u,int F)
	{
		f[u][0]=1;
		int v;
		fo(i,u)
			if((v=to[i])!=F)
			{
				dfs(v,u);
				memset(_f,0,sizeof(_f));
				fr(j,0,s[u])
					fr(k,0,s[v])
						if(w[i])
						{
							_f[j+k]=(_f[j+k]+f[u][j]*f[v][k])%mod;
						}
						else
						{
							_f[j]=(_f[j]+f[u][j]*f[v][k])%mod;
							_f[j+k]=(_f[j+k]-f[u][j]*f[v][k]%mod+mod)%mod;
						}
				s[u]+=s[v];
				fr(i,0,s[u])
					f[u][i]=_f[i];
			}
		fr(i,0,s[u])
		{
			_f[i]=f[u][i];
			f[u][i]=0;
		}
		fr(i,0,s[u])
			fr(j,1,3)
				f[u][i+j]=(f[u][i+j]+a[u][j]*_f[i]%mod*j*inv[i+j]%mod)%mod;
		s[u]+=3;
	}
	int main()
	{
		n=read();
		fr(i,1,n)
		{
			a[i][1]=read();
			a[i][2]=read();
			a[i][3]=read();
			a[i][0]=power(a[i][1]+a[i][2]+a[i][3],mod-2,mod);
			a[i][1]=a[i][1]*a[i][0]%mod;
			a[i][2]=a[i][2]*a[i][0]%mod;
			a[i][3]=a[i][3]*a[i][0]%mod;
//			printf("%lld %lld %lld\n",a[i][1],a[i][2],a[i][3]);
		}
		fr(i,1,n-1)
		{
			int u=read(),v=read();
			add(u,v,1);
			add(v,u,0);
		}
		fr(i,1,n*3)
			inv[i]=power(i,mod-2,mod);
		dfs(1,0);
		fr(i,1,n*3)
			ans=(ans+f[1][i])%mod;
//		fr(i,1,n)
//			fr(j,0,s[i])
//				printf("%lld%c",f[i][j],j==s[i]?'\n':' ');
		printf("%lld\n",ans);
		return 0;
	}
}
int main()
{
	return run::main();
}
