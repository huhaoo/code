/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Tue 12 May 2020 09:12:48 PM CST
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
const int N=5010,mod=998244353;
i64 n,f[N],F[N];
i64 power(i64 a,i64 b,i64 p)
{
	if(b<0) return 0;
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2,mod); }
i64 C(i64 a,i64 b){ return a>=b&&b>=0?f[a]*F[b]%mod*F[a-b]%mod:0; }
int g[N][N],G[N][N],ans[N];
int main()
{
	n=read(); f[0]=1;
	fr(i,1,n) f[i]=f[i-1]*i%mod;
	F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	g[0][0]=1;
	fr(i,1,n) fr(j,1,i) fr(k,1,i:q
			)
	return 0;
}
