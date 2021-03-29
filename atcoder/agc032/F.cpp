/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Thu 16 Jan 2020 06:26:45 PM CST
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
const int N=1000010,mod=1000000007;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	while(b)
	{
		if(b&1) r=r*a%p;
		a=a*a%p; b>>=1;
	}
	return r;
}
i64 inv(i64 a){ return power(a,mod-2,mod); }
namespace C
{
	i64 f[N],F[N];
	void init(int n)
	{
		f[0]=1;
		fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]);
		fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 C(i64 a,i64 b){ return f[a]*F[b]%mod*F[a-b]%mod; }
	i64 inv(i64 a){ return F[a]*f[a-1]%mod; }
}
int n;
i64 f[3],F[3],ans;
int main()
{
	n=read()-1; C::init(n+3); f[0]=1;
	fr(i,1,n+1)
	{
		fr(j,0,2){ F[j]=f[j]; f[j]=0; }
		fr(j,0,2) fr(k,0,2) if(j!=k) f[j]=(f[j]+F[k])%mod;
//		printf("%lld ",f[1]*C::C(n+1,i)%mod);
		ans=(ans+f[1]*C::C(n+1,i)%mod*power(3,mod-1-(n+1),mod)%mod*C::inv(n+1)%mod*C::inv(i))%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
