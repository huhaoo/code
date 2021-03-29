/**************************************************************
	File name: 1641.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 10/29/2018, 1:55:20 PM
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
#define mod 20100403
long long n,m;
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
long long f(long long x)
{
	long long r=1;
	fr(i,1,x)r=r*i%mod;
	return r;
}
long long c(long long a,long long b)
{
	return f(a)*power(f(b),mod-2,mod)%mod*power(f(a-b),mod-2,mod)%mod;
}
int main()
{
	n=read();m=read();
	printf("%lld\n",(c(n+m,m)-c(n+m,m-1)+mod)%mod);
	return 0;
}