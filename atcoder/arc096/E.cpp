/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Mon 08 Jun 2020 03:55:44 PM CST
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
const int N=3010;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 n,mod,ans,s[N][N],c[N][N];
i64 &Add(i64 &a,i64 b){ return a=(a+b)%mod; }
int main()
{
	n=read(); mod=read();
	s[0][0]=1; c[0][0]=1;
	fr(i,1,n+1) c[i][0]=1;
	fr(i,1,n+1) fr(j,1,i){ s[i][j]=(s[i-1][j]*j+s[i-1][j-1])%mod; c[i][j]=(c[i-1][j]+c[i-1][j-1])%mod; }
	fr(i,0,n)
	{
		i64 v=power(2,power(2,n-i,mod-1),mod);
		fr(k,0,i) Add(ans,(i&1?mod-1:1)*c[n][i]%mod*s[i+1][k+1]%mod*power(2,(n-i)*k,mod)%mod*v);
	}
	printf("%lld\n",ans);
	return 0;
}
