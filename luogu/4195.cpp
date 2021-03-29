/**************************************************************
	File name: 4195.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/20/2019, 1:37:02 PM
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
long long gcd(long long a,long long b)
{
	return b?gcd(b,a%b):a;
}
long long inv(long long a,long long b)
{
	long long x,y;
	exgcd(a,b,x,y);
	return (x%b+b)%b;
}
#include<unordered_map>
long long a,p,b;
unordered_map<long long,long long>m;
int main()
{
	while((a=read())&&(p=read())&&(b=read()))
	{
		if(b==1)
		{
			printf("0\n");
			continue;
		}
		long long g,s=0;
		long long k=1,kk=1;
		while((g=gcd(a,p))!=1)
		{
			if(b%g!=0)
				break;
			s++;
			p/=g;
			b=b/g*inv(a/g,p)%p;
		}
		if(g!=1)
		{
			printf("No Solution\n");
			continue;
		}
		m.clear();
		fr(i,0,sqrt(p))
		{
			if(!m[k])
				m[k]=i+1;
			k=k*a%p;
//			printf("- %lld\n",k);
		}
		k=inv(k,p);
		fr(i,0,sqrt(p)+1)
		{
			long long x=b*kk%p;
			if(m[x])
			{
				printf("%lld\n",i*int(sqrt(p)+1)+m[x]-1+s);
				break;
			}
			kk=kk*k%p;
			if(i==_end_)
				printf("No Solution\n");
		}
	}
	return 0;
}