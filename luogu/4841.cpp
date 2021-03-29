/***************************************************************
	File name: 4841.cpp
	Author: huhao
	Create time: Mon 14 Oct 2019 04:45:25 PM CST
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
#include<stdlib.h>
const i64 mod=1004535809;
const i64 g=3;
const i64 p=power(g,mod-2,mod),i2=power(2,mod-2,mod);
const i64 N=(1<<18)+10;
int sqrt_check(i64 k)
{
	return power(k,(mod-1)/2,mod)==1;
}
i64 sqrt_i64(i64 k)
{
	if(k==0)
		return 0;
	if(!sqrt_check(k))
		return -1;
	i64 a=rand()%mod;
	while(sqrt_check((a*a-k)%mod))
		a=rand()%mod;
	i64 a1=a,a2=1,r1=1,r2=0,b=(mod+1)/2;
	while(b)
	{
		if(b&1)
		{
			i64 _r=r1;
			r1=(a1*r1+a2*r2%mod*((a*a-k)%mod))%mod;
			r2=(a1*r2+_r*a2)%mod;
		}
		i64 _r=a1;
		a1=(a1*a1+a2*a2%mod*((a*a-k)%mod))%mod;
		a2=(_r*a2+a2*_r)%mod;
		b>>=1;
	}
	return min(mod-r1,r1);
}
i64 r[N],l;
void NTT(i64 *a,i64 opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		i64 wn=power(opt==1?g:p,(mod-1)>>(i+1),mod);
		for(i64 j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			i64 w=1;
			fr(k,0,(1<<i)-1)
			{
				i64 x=a[j+k],y=w*a[(1<<i)+j+k]%mod;
				a[j+k]=(x+y)%mod;
				a[(1<<i)+j+k]=(x-y+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
	if(opt==-1)
	{
		int _i=power(1<<l,mod-2,mod);
		fr(i,0,(1<<l)-1)
			a[i]=a[i]*_i%mod;
	}
}
i64 _a[N],_b[N];
void mul(i64 *c,i64 *a,i64 *b,i64 n,i64 m)
{
	l=0;
	while(n+m+1>(1<<l))
		l++;
	fr(i,1,(1<<l)-1)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,0,(1<<l)-1)
		_a[i]=_b[i]=0;
	fr(i,0,n)
		_a[i]=a[i];
	fr(i,0,m)
		_b[i]=b[i];
	NTT(_a,1);
	NTT(_b,1);
	fr(i,0,(1<<l)-1)
		c[i]=_a[i]*_b[i]%mod;
	NTT(c,-1);
}
i64 _c[N];
void inv(i64 *b,i64 *a,i64 n)
{
	if(n==1)
	{
		b[0]=power(a[0],mod-2,mod);
		return;
	}
	inv(b,a,(n+1)/2);
	//g(f(x))=1/f(x)-h(x)=0
	//f(x)=2f0(x)-h(x)f0^2(x)
	mul(_c,b,a,n-1,n-1);
	fr(i,n,n+n-2)
		_c[i]=0;
	fr(i,1,n-1)
		_c[i]=(mod-_c[i])%mod;
	_c[0]=(2+mod-_c[0])%mod;
	mul(b,b,_c,n-1,n-1);
	fr(i,n,n+n-2)
		b[i]=0;
}
i64 _d[N];
void sqrt_poly(i64 *b,i64 *a,i64 n)
{
	if(n==1)
	{
		b[0]=sqrt_i64(a[0]);
		return;
	}
	sqrt_poly(b,a,(n+1)/2);
	//g(f(x))=f^2(x)-h(x)=0
	//f(x)=f0(x)+h/f0(x)
	fr(i,0,n-1)
		_d[i]=0;
	inv(_d,b,n);
	mul(_d,_d,a,n-1,n-1);
	fr(i,n,n+n-2)
		_d[i]=0;
	fr(i,0,n-1)
		b[i]=(b[i]+mod+_d[i])*i2%mod;
}
i64 _e[N];
void d(i64 *b,i64 *a,i64 n)
{
	fr(i,1,n-1)
		b[i-1]=a[i]*i%mod;
	b[n-1]=0;
}
void integral(i64 *b,i64 *a,i64 n)
{
	fr(i,1,n-1)
		b[i]=a[i-1]*power(i,mod-2,mod)%mod;
	b[0]=0;
}
i64 _g[N];
void ln(i64 *b,i64 *a,i64 n)
{
	//(ln f(x))'=f'(x)/f(x)
	inv(_g,a,n);
	d(b,a,n);
	mul(_g,_g,b,n-1,n-1);
	fr(i,n,n+n-2)
		_g[i]=0;
	integral(b,_g,n);
}
i64 n,a[N],b[N];
int checkg(i64 g)
{
	i64 r=1;
	fr(i,1,mod-2)
	{
		r=r*g%mod;
		if(r==1)
		{
			printf("%lld^%d=1\n",g,i);
			return 0;
		}
	}
	return 1;
}
namespace Choose
{
	i64 f[N],F[N];
	void init(int n)
	{
		f[0]=1;
		fr(i,1,n)
			f[i]=f[i-1]*i%mod;
		F[n]=power(f[n],mod-2,mod);
		fd(i,n,1)
			F[i-1]=F[i]*i%mod;
	}
	i64 inv(i64 n)
	{
		return F[n]*f[n-1]%mod;
	}
}
int main()
{
	srand((unsigned long long)new char);
	n=read();
	Choose::init(n);
	fr(i,0,n)
		a[i]=power(2,(long long)i*(i-1)/2,mod)*Choose::F[i]%mod;
	ln(b,a,n+1);
	printf("%lld\n",b[n]*Choose::f[n]%mod);
	return 0;
}
