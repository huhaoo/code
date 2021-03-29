/**************************************************************
	File name: 4980.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/19/2019, 10:31:25 AM
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
#define mod 1000000007
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
long long phi(long long n)
{
	long long k=n;
	fr(i,2,sqrt(k))
		if(k%i==0)
		{
			n=n/i*(i-1);
			while(k%i==0)
				k/=i;
			_end_=sqrt(k);
		}
	if(k!=1)
		n=n/k*(k-1);
	return n;
}
long long calc(long long n)
{
	long long s=0;
	fr(i,1,sqrt(n))
	{
		if(n%i!=0)
			continue;
		s=(s+pow(n,i-1,mod)*phi(n/i))%mod;
		if(i*i!=n)
			s=(s+pow(n,n/i-1,mod)*phi(i))%mod;
	}
	return s;
}
int main()
{
	fr(T,1,read())
		printf("%lld\n",calc(read()));
	return 0;
}