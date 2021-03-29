/***************************************************************
	File name: 4389.cpp
	Author: huhao
	Create time: Sun 05 May 2019 03:59:39 PM CST
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
const int N=(1<<20)+10;
const long long mod=998244353,g=3,ig=332748118;
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
int r[N],l;
void NTT(long long *a,int opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		long long wn=power(opt==1?g:ig,(mod)>>(i+1),mod);
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			long long w=1;
			fr(k,0,(1<<i)-1)
			{
				long long x=a[j+k],y=a[j+k+(1<<i)]*w%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+(1<<i)]=(x-y+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
	if(opt==-1)
	{
		long long i=power(1<<l,mod-2,mod);
		fr(j,0,(1<<l)-1)
			a[j]=a[j]*i%mod;
	}
}
long long _a[N],_b[N];
void mul(long long *o,long long *a,long long *b,long long n,long long m)
{
	l=0;
	while((1<<l)<n+m+1)
		l++;
	fr(i,0,(1<<l)-1)
	{
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		_a[i]=_b[i]=0;
	}
	fr(i,0,n)
		_a[i]=a[i];
	fr(i,0,m)
		_b[i]=b[i];
	NTT(_a,1);
	NTT(_b,1);
	fr(i,0,(1<<l)-1)
		o[i]=_a[i]*_b[i]%mod;
	NTT(o,-1);
}
long long x[N];
/*
 * g(f(x))=1/f(x)-h(x)
 * f(x)=f0(x)-g(f0(x))/g'(f0(x))=f0(x)-(1/f0(x)-h(x))/(-1/f0^2(x))=2f0(x)-h(x)f0^2(x)
 */
void inv(long long *o,long long *a,int p)
{
	if(p==1)
	{
		*o=power(*a,mod-2,mod);
		return;
	}
	int _p=(p+1)>>1;
	inv(o,a,_p);
	mul(x,o,a,p-1,p-1);
	fr(i,0,p-1)
		x[i]=(-x[i]+mod)%mod;
	x[0]=(x[0]+2)%mod;
	mul(o,x,o,p-1,p-1);
	fr(i,p,p+p-2)
		o[i]=0;
}
void d(long long *o,long long *a,long long p)
{
	fr(i,0,p-2)
		o[i]=a[i+1]*(i+1)%mod;
	o[p-1]=0;
}
namespace _inv_
{
	long long f[N],fi[N];
	void init(int n=0)
	{
		f[0]=1;
		fr(i,1,n)
			f[i]=f[i-1]*i%mod;
		fi[n]=power(f[n],mod-2,mod);
		fd(i,n,1)
			fi[i-1]=fi[i]*i%mod;
	}
	long long inv(int a)
	{
		return fi[a]*f[a-1]%mod;
	}
}
void integral(long long *o,long long *a,long long p)
{
	fd(i,p-1,1)
		o[i]=a[i-1]*_inv_::inv(i)%mod;
	o[0]=0;
}
long long y[N];
void ln(long long *o,long long *a,long long p)
{
	d(y,a,p);
	inv(o,a,p);
	mul(y,o,y,p-1,p-1);
	integral(o,y,p);
}
long long z[N];
/*
 * g(f(x))=e^h(x)-f(x)=ln(f(x))-h(x)=0
 * f(x)=(1-ln(f0(x))+h(x))f0(x)
 */
void exp(long long *o,long long *a,long long p)
{
	if(p==1)
	{
		o[0]=1;
		return;
	}
	int _p=(p+1)>>1;
	exp(o,a,_p);
	ln(z,o,p);
	fr(i,0,p-1)
		z[i]=(a[i]-z[i]+mod)%mod;
	z[0]=(z[0]+1)%mod;
	mul(o,z,o,p-1,p-1);
	fr(i,p,p+p-2)
		o[i]=0;
}
long long a[N],f[N],ans[N],n,m;
int main()
{
	m=read();
	n=read();
	_inv_::init(n+1);
	fr(i,1,m)
		a[read()]++;
	fr(i,1,n)
		fr(j,1,n/i)
			f[i*j]=(f[i*j]+a[i]*i%mod*_inv_::inv(i*j)%mod)%mod;
//	fr(i,1,n)
//		printf("%lld%c",f[i],i==n?'\n':' ');
	exp(ans,f,n+1);
	fr(i,1,n)
		printf("%lld\n",ans[i]);
	return 0;
}
