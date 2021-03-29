/***************************************************************
	File name: 4769.cpp
	Author: huhao
	Create time: Sat 25 May 2019 04:45:40 PM CST
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
const long long N=1200010,mod=998244353;
long long power(long long a,long long b,long long p)
{
	long long r=1;
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
long long f_[N],_f[N],n=1200000,a[N],p[N];
long long C(long long a,long long b)
{
	return f_[a]*_f[b]%mod*_f[a-b]%mod;
}
int main()
{
	f_[0]=1;
	fr(i,1,n)
		f_[i]=f_[i-1]*i%mod;
	_f[n]=power(f_[n],mod-2,mod);
	fd(i,n,1)
		_f[i-1]=_f[i]*i%mod;
	fr(_t,1,read())
	{
		long long m=0,_m=1,ans=0;
		n=read();
		fr(i,1,n)
		{
			a[i]=read();
			p[i]=0;
		}
		fr(i,1,n)
		{
			p[a[i]]=1;
			long long k=max(m,a[i])+1;
			ans=(ans+C(n-i+n-k+1,n-k)-C(n-i+n-k+1,n-k-1)+mod)%mod;
			if(a[i]>m)
				m=a[i];
			else
			{
				if(a[i]!=_m)
					break;
			}
			while(p[_m])
				_m++;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
