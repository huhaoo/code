/**************************************************************
	File name: 4720.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/13/2019, 2:00:45 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
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
#define N 100
long long a,b,d,c[N],p[N],m[N],t,s[N],ans;
long long exgcd(long long a,long long b,long long &x,long long &y)
{
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	long long g=exgcd(b,a%b,x,y),k;
	k=x;
	x=y;
	y=k-(a/b)*y;
	return g;
}
long long inv(long long a,long long b)
{
	long long x,y;
	exgcd(a,b,x,y);
	return (x%b+b)%b;
}
long long pow(long long a,long long b,long long m)
{
	if(b<=0)
		return 1;
	long long r=1;
	a%=m;
	while(b)
	{
		if(b&1)
			r=r*a%m;
		a=a*a%m;
		b>>=1;
	}
	return r;
}
long long calc(long long x,long long p,long long c)
{
	if(c<=0)
		return 1;
	long long n=pow(p,c,1ll<<60),r=1,k=1;
	if(x>=p)
		r=r*calc(x/p,p,c)%n;
	fr(i,(x/n)*n+1,x)
		if(i%p!=0)
			r=r*(i%n)%n;
	fr(i,1,n)
		if(i%p!=0)
			k=k*(i%n)%n;
	return r*pow(k,x/n,n)%n;
}
long long calc(long long x,long long p)
{
	long long r=0;
	while(x>=p)
	{
		x/=p;
		r+=x;
	}
	return r;
}
void init(int d)
{
	fr(i,2,sqrt(d))
		if(d%i==0)
		{
			t++;
			p[t]=i;
			while(d%i==0)
			{
				d/=i;
				c[t]++;
			}
			_end_=sqrt(d);
		}
	if(d!=1)
	{
		t++;
		p[t]=d;
		c[t]=1;
	}
}
int main()
{
	a=read();
	b=read();
	d=read();
	init(d);
	fr(i,1,t)
	{
		s[i]=pow(p[i],c[i],1ll<<60);
		long long _c=c[i]-calc(a,p[i])+calc(b,p[i])+calc(a-b,p[i]);
		m[i]=calc(a,p[i],_c)*inv(calc(b,p[i],_c),s[i])%s[i]*inv(calc(a-b,p[i],_c),s[i])%s[i]*pow(p[i],c[i]-_c,1ll<<60)%s[i];
	}
	fr(i,1,t)
		ans=(ans+d/s[i]*inv(d/s[i],s[i])%d*m[i])%d;
	printf("%lld\n",ans);
	return 0;
}