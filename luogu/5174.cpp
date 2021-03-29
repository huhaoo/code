/**************************************************************
	File name: 5174.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 1/5/2019, 10:48:35 AM
**************************************************************/
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
#define mod 1000000007
long long n,ans,sn;
long long pow(long long a,long long b,long long m)
{
	long long r=1;
	a%=m;
	while(b)
	{
		if(b&1)
			r=r*a%m;
		a=a*a%m;
		b>>=1;
	}
	return r;
}
long long p6=pow(6,mod-2,mod);
long long calc(long long a)
{
	a%=mod;
	return a*(a+1)%mod*(2*a+1)%mod*p6%mod;
}
int main()
{
	n=read();
	sn=sqrt(n);
	fr(i,1,sn)
	{
		long long k=sqrt(n-i*i);
		ans=(ans+i%mod*i%mod*k%mod+calc(k))%mod;
	}
	printf("%lld\n",(ans+calc(sn))%mod*4%mod);
	return 0;
}