/***************************************************************
	File name: 5591.cpp
	Author: huhao
	Create time: Tue 15 Oct 2019 02:56:56 PM CST
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
#define i64 long long
const i64 mod=998244353,g=3;
i64 power(i64 a,i64 b,i64 p)
{
	a%=p;
	i64 r=1;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
i64 n,p,k,ans,K,w;
i64 calc(i64 n,i64 a)
{
	if(a==1)
		return (n*(n+1)/2)%mod;
	i64 A=power(a-1,mod-2,mod),B=power(a,n+1,mod);
	return (A*(n*B%mod-A*(B-a)%mod)%mod+mod)%mod;
}
int main()
{
	n=read();
	p=read();
	k=read();
	K=power(k,mod-2,mod);
	ans=power(1+p,n-1,mod)*n%mod*p%mod;
	w=power(g,(mod-1)/k,mod);
	fr(l,0,k-1)
	{
		i64 a=power(w,l,mod);
		i64 A=power(p*a+1,n,mod);
		ans=(ans-K*A%mod*calc(k-1,power(a,mod-2,mod))%mod+mod)%mod;
//		fr(j,1,k-1)
//			ans=(ans-K*A%mod*j%mod*power(a,mod-1-j,mod)%mod+mod)%mod;
	}
	printf("%lld\n",ans*K%mod);
	return 0;
}
