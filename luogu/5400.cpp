/***************************************************************
	File name: 5400.cpp
	Author: huhao
	Create time: Fri 20 Sep 2019 04:45:10 PM CST
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
const int N=5000010,mod=998244353;
i64 T,n,m,l,k,f[N],F[N],ans,S,inv[N],M,c[N],a[N];
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	a%=mod;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
i64 C(i64 a,i64 b)
{
	return f[a]*F[b]%mod*F[a-b]%mod;
}
i64 P(i64 a,i64 b)
{
	return f[a]*F[a-b]%mod;
}
void getinv(i64 *a,i64 *inv,i64 n)
{
	inv[1]=a[1];
	fr(i,2,n)
		inv[i]=inv[i-1]*a[i]%mod;
	inv[n]=power(inv[n],mod-2,mod);
	fd(i,n,2)
	{
		i64 I=inv[i];
		inv[i]=inv[i]*inv[i-1]%mod;
		inv[i-1]=I*a[i]%mod;
	}
}
int main()
{
	n=5000000;
	f[0]=1;
	fr(i,1,n)
		f[i]=f[i-1]*i%mod;
	F[n]=power(f[n],mod-2,mod);
	fd(i,n,1)
		F[i-1]=F[i]*i%mod;
	T=read();
	while(T--)
	{
		n=read();
		m=read();
		l=read();
		k=read();
		M=min(min(n,m),l);
		fr(i,0,M)
			c[i]=(n-i)*(m-i)%mod*(l-i)%mod;
		fr(i,1,M)
			a[i]=(c[0]-c[i]+mod)%mod;
		getinv(a,inv,M);
		ans=0;
		S=1;
		fr(i,1,k-1)
			S=S*inv[i]%mod;
		fr(i,k,M)
		{
			S=S*inv[i]%mod;
			ans=ans+((i-k)&1?-1:1)*C(i,k)%mod*P(n,i)%mod*P(m,i)%mod*P(l,i)%mod*S%mod;
		}
		printf("%lld\n",(ans%mod+mod)%mod);
	}
	return 0;
}
