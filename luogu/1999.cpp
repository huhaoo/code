/**************************************************************
	File name: 1999.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/4/2018, 1:14:46 PM
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
#define N 100010
#define k 100000
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
long long f[N],pf[N],n,m,t,p[N];
int main()
{
	f[0]=p[0]=1;
	fr(i,1,k)
		f[i]=f[i-1]*i%mod,p[i]=p[i-1]*2%mod;
	pf[k]=power(f[k],mod-2,mod);
	fd(i,k-1,0)pf[i]=pf[i+1]*(i+1)%mod;
	n=read();
	m=read();
	printf("%lld\n",n>=m?f[n]*pf[m]%mod*pf[n-m]%mod*p[n-m]%mod:0);
	return 0;
}