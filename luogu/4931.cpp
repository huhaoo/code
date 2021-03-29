/***************************************************************
	File name: 4931.cpp
	Author: huhao
	Create time: Tue 07 May 2019 03:41:47 PM CST
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
const int N=10000010;
const long long mod=998244353;
long long f[N],fi[N],n,s[N],p2[N],i2[N],g[N];
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
int main()
{
	n=5000000;
//	n=20;
	f[0]=1;
	fr(i,1,n*2)
		f[i]=f[i-1]*i%mod;
	fi[n*2]=power(f[n*2],mod-2,mod);
	fd(i,n*2,1)
		fi[i-1]=fi[i]*i%mod;
	p2[0]=i2[0]=1;
	p2[1]=2;
	i2[1]=power(2,mod-2,mod);
	fr(i,2,n*2)
	{
		p2[i]=p2[i-1]*p2[1]%mod;
		i2[i]=i2[i-1]*i2[1]%mod;
	}
	s[0]=s[1]=1;
	fr(i,2,n)
		s[i]=(s[i-1]+s[i-2]*i2[1]%mod*fi[i]%mod*f[i-1])%mod;
	g[0]=1;
	fr(i,1,n)
		g[i]=(s[i]-s[i-1]+mod)%mod*f[i]%mod*f[i]%mod*p2[i*2]%mod;
	fr(T,1,read())
	{
		int i=read(),j=read();
		long long k=f[i]*fi[j]%mod*fi[i-j]%mod;
		printf("%lld\n",k*k%mod*f[j]%mod*p2[j]%mod*g[i-j]%mod);
	}
	return 0;
}
