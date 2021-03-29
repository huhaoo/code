/**************************************************************
	File name: 4339.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 12/31/2018, 9:22:49 AM
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
long long n,k;
long long gcd(long long a,long long b){return b?gcd(b,a%b):a;}
long long calc(long long a,long long b,long long c)
{
	long long d=gcd(b,c);
	if(d==1)
		return a;
	else if(a>c/d)
		return b*(c-a)/d+calc((c-b*(c-a))/d,b,c/d);
	else
		return a;
}
int main()
{
	fr(T,1,read())
	{
		k=read();
		n=read();
		printf("%lld\n",calc(n-1,k,n)+1);
	}
	return 0;
}
//Must use "__int128"