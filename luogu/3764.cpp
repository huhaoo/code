/****************************************************************
	File name: 3764.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/8/2018, 7:12:09 PM
****************************************************************/
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
long long gcd(long long a,long long b)
{
	return b?gcd(b,a%b):a;
}
#define N 4010
long long ans,n,i,j,x,y;
int main()
{
	n=read();
	i=1;
	while(i<=n)
	{
		x=n/i;y=log(i)/log(2);
		j=min(n/x,1ll<<(y+1));
		ans+=(j-i+1+(j&1))/2*x*y;
		i=j+1;
	}
	printf("%lld\n",ans*2);
	return 0;
}