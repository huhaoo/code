/***************************************************************
	File name: 5323.cpp
	Author: huhao
	Create time: Tue 30 Apr 2019 08:35:00 AM CST
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
const int mod=1000000007,N=500010;
long long power(long long a,long long b,long long p)
{
	a%=p;
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
int n;
long long a[N],b[N],c[N],i100=power(100,mod-2,mod),s1[N],s2[N],s3,ans[N];
int main()
{
	n=read();
	fr(i,1,n)
	{
		a[i]=read()*i100%mod;
		b[i]=read()*i100%mod;
	}
	c[1]=a[1];
	s1[0]=s2[0]=1;
	fr(i,1,n)
		s1[i]=s1[i-1]*a[i]%mod;
	s2[1]=c[1];
	fr(i,2,n)
	{
		s3=(s3+b[i-1]*power(s1[i-1]*s2[i-1],mod-2,mod))%mod;
		c[i]=power(mod+1-b[i]*s2[i-1]%mod*s1[i-1]%mod*s3%mod,mod-2,mod)*a[i]%mod;
		s2[i]=s2[i-1]*c[i]%mod;
	}
	ans[n+1]=1;
	fd(i,n,1)
		ans[i]=ans[i+1]*c[i]%mod;
	printf("%lld\n",ans[1]);
	return 0;
}
