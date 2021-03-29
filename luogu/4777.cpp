/**************************************************************
	File name: 4777.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/10/2019, 9:00:34 AM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(__int128 i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(__int128 i=(a),_end_=(b);i>=_end_;i--)
__int128 read()
{
	__int128 r=0,t=1,c=getchar();
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
__int128 n;
__int128 a1,a2,b1,b2,k1,k2,g;
__int128 exgcd(__int128 a,__int128 b,__int128 &x,__int128 &y)//ax+by=gcd(a,b)
{
	if(!b)
	{
		x=1;
		y=0;
		return a;
	}
	__int128 g=exgcd(b,a%b,x,y),k;
	k=x;
	x=y;
	y=k-(a/b)*y;
	return g;
}
int main()
{
	n=read()-1;
	a1=read();
	b1=read();
	fr(i,1,n)
	{
		a2=read();
		b2=read();
		g=exgcd(a1,a2,k1,k2);
//		k2=-k2;
		k1*=(b2-b1)/g;
//		k2*=(b2-b1)/g;
		b1=k1*a1+b1;
		a1*=a2/g;
		b1=(b1%a1+a1)%a1;
	}
	printf("%lld\n",(long long)(b1));
	return 0;
}