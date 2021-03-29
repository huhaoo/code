/**************************************************************
	File name: 5170.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/12/2019, 11:00:24 AM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define mod 998244353
#define p2 499122177
#define p6 166374059
void calc(long long n,long long a,long long b,long long c,long long &f,long long &g,long long &h,int opt)
{
	long long _f,_g,_h;
	if(a*n+b<c)
	{
		f=g=h=0;
		return;
	}
	if(a>=c||b>=c)
	{
		calc(n,a%c,b%c,c,_f,_g,_h,1);
		f=(n*(n+1)/2%mod*(a/c)%mod+(n+1)*(b/c)%mod+_f)%mod;
		g=(n*(n+1)%mod*(n+n+1)%mod*p6%mod*(a/c)%mod+n*(n+1)/2%mod*(b/c)%mod+_g)%mod;
		h=((a/c)*(a/c)%mod*n%mod*(n+1)%mod*(n+n+1)%mod*p6%mod+(a/c)*(b/c)%mod*n%mod*(n+1)%mod+(n+1)*(b/c)%mod*(b/c)%mod+2*(a/c)*_g%mod+2*(b/c)*_f%mod+_h)%mod;
//		printf("+ n:%lld a:%lld b:%lld c:%lld f:%lld g:%lld h:%lld\n",n,a,b,c,f,g,h);
		return;
	}
	long long m=(n*a+b)/c-1;
	calc(m,c,c-b-1,a,_f,_g,_h,1);
	f=(n*(m+1)%mod-_f+mod)%mod;
	g=((m+1)*(n+1)%mod*n%mod-_h-_f+mod+mod)*p2%mod;
	h=(n*(m+1)%mod*(m+2)%mod-2*_g-2*_f-f+5ll*mod)%mod;
//	printf("- n:%lld a:%lld b:%lld c:%lld f:%lld g:%lld h:%lld\n",n,a,b,c,f,g,h);
}
int main()
{
	long long t,n,a,b,c,f,g,h;
	t=read();
	while(t--)
	{
		n=read();
		a=read();
		b=read();
		c=read();
		calc(n,a,b,c,f,g,h,1);
		printf("%lld %lld %lld\n",f,h,g);
	}
	return 0;
}