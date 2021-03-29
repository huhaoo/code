/***************************************************************
	File name: 5472.cpp
	Author: huhao
	Create time: Wed 31 Jul 2019 09:53:18 AM CST
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
const i64 N=10,mod=998244353,M=10000010;
i64 n,m,k,f[N],v[N],fac[M],inv[M];
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	a%=p;
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
	return fac[a]*inv[b]%mod*inv[a-b]%mod;
}
i64 calc(i64 x,i64 a,i64 b,i64 p)
{
	if(x<=p&&x<=a&&p-x<=b)
		return C(p-1,x-1)*fac[a+b-p]%mod*inv[a+b]%mod*fac[a]%mod*inv[a-x]%mod*fac[b]%mod*inv[b-(p-x)]%mod;
	return 0;
}
int main()
{
	freopen("landlords.in","r",stdin);
	freopen("landlords.out","w",stdout);
	n=read();
	m=read();
	k=read();
	f[k]=1;
	fac[0]=1;
	fr(i,1,n)
		fac[i]=fac[i-1]*i%mod;
	inv[n]=power(fac[n],mod-2,mod);
	fd(i,n,1)
		inv[i-1]=inv[i]*i%mod;
	while(m--)
	{
		i64 p=read();
		fr(i,1,k+1)
			v[i]=0;
		fr(i,1,min(k+1,p))
		{
			i64 w=(f[2]*i%mod*i+f[1]*i+f[0])%mod;
			fr(j,1,k+1)
				v[j]=(v[j]+w*calc(i,p,n-p,j))%mod;
		}
		fr(i,1,min(k+1,n-p))
		{
			i64 w=(f[2]*(i+p)%mod*(i+p)+f[1]*(i+p)+f[0])%mod;
			fr(j,1,k+1)
				v[j]=(v[j]+w*calc(i,n-p,p,j))%mod;
		}
		if(k==1)
		{
			f[1]=(v[2]-v[1]+mod)%mod;
			f[0]=(v[1]-f[1]+mod)%mod;
		}
		else
		{
			i64 i2=power(2,mod-2,mod);
			f[2]=((v[3]-2*v[2]+v[1])%mod+mod)*i2%mod;
			f[1]=((v[2]*8-v[1]*5-v[3]*3)%mod+mod)*i2%mod;
			f[0]=((v[1]*3-v[2]*3+v[3])%mod+mod)%mod;
		}
	}
	fr(T,1,read())
	{
		i64 v=read();
		printf("%lld\n",(f[2]*v%mod*v+f[1]*v+f[0])%mod);
	}
	return 0;
}
