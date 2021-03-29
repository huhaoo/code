/****************************************************************
	File name: 4781.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/26/2018, 1:07:31 PM
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
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
#define mod 998244353
long long power(long long x,long long y,long long p)
{
	long long r=1;
	while(y)
	{
		if(y&1)r=r*x%p;
		x=x*x%p;
		y>>=1;
	}
	return r;
}
#define N 2010
long long x[N],y[N],n,v,ans;
int main()
{
	n=read();
	v=read();
	fr(i,1,n)x[i]=read(),y[i]=read();
	fr(i,1,n)
	{
		long long k=1;
		fr(j,1,n)if(i!=j)k=k*(x[i]+mod-x[j])%mod;
		k=power(k,mod-2,mod);
		fr(j,1,n)if(i!=j)k=k*(v+mod-x[j])%mod;
		k=k*y[i]%mod;
		ans=(ans+k)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}