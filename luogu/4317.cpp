/****************************************************************
	File name: 4317.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 10/16/2018, 8:46:18 PM
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
#define B 60
#define mod 10000007
long long n,f[B+10][B+10][2],ans=1;
long long power(long long x,long long y,long long p)
{
	long long r=1;
	while(y)
	{
		if(y&1)r=r*x%p;
		x=x*x%p;
		y>>=1;
	}
	return r;
}
int main()
{
	n=read();
	f[B+1][0][0]=1;
	fd(i,B,0)
		fr(j,0,B)
		{
			f[i][j][1]=f[i][j][1]+f[i+1][j][1];
			f[i][j+1][1]=f[i][j+1][1]+f[i+1][j][1];
			if(n&(1ll<<i))
			{
				f[i][j][1]=f[i][j][1]+f[i+1][j][0];
				f[i][j+1][0]=f[i][j+1][0]+f[i+1][j][0];
			}
			else f[i][j][0]=f[i][j][0]+f[i+1][j][0];
		}
	fr(i,1,B)ans=ans*power(i,f[0][i][0]+f[0][i][1],mod)%mod;
	printf("%lld\n",ans);
	return 0;
}