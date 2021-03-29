/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Mon 08 Jun 2020 02:46:44 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=1<<16|10,M=40,mod=1000000007;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2,mod); }
i64 n,m,a[N],ans,f[M][N];
namespace C
{
	i64 f[N],F[N];
	void init(int n)
	{
		f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 C(i64 a,i64 b){ return a>=b&&b>=0?f[a]*F[b]%mod*F[a-b]%mod:0; }
}
i64 &Add(i64 &a,i64 b){ return a=(a+b)%mod; }
int main()
{
	n=read(); m=read(); C::init(1<<n);
	fr(i,0,m-1) a[m-i]=read();
	f[0][0]=1;
	fr(i,1,m) fr(j,0,(1<<n)-1)
	{
		Add(f[i][j],f[i-1][j]);
		fr(k,0,n-1) if(!((j>>k)&1)) Add(f[i][j|(1<<k)],-f[i-1][j]*C::C((1<<n)-j-a[i],(1<<k)-1)%mod*C::f[1<<k]);
	}
//	fr(i,0,(1<<n)-1) printf("%lld%c",f[m][i]*C::f[(1<<n)-1-i]%mod,i==end_i?'\n':' ');
	fr(i,0,(1<<n)-1) Add(ans,f[m][i]*C::f[(1<<n)-1-i]);
	printf("%lld\n",(ans*(1<<n)%mod+mod)%mod);
	return 0;
}
