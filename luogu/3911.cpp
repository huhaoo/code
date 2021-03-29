/**************************************************************
	File name: 3911.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/1/2018, 11:15:17 AM
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
#define N 50010
long long n=50000,a[N],mu[N],g[N],ans;
int main()
{
	fr(i,1,read())a[read()]++;
	fr(x,1,n)
	{
		fr(i,1,n/x)g[x]+=i*a[i*x];
		g[x]*=g[x];
	}
	fr(i,1,n)
	{
		mu[i]=1;
		int k=i;
		fr(j,2,sqrt(i))
			if(k%j==0)
			{
				if((k/j)%j==0)
				{
					mu[i]=0;
					break;
				}
				mu[i]=-mu[i];
				k/=j;
			}
		if(k!=1&&mu[i]!=0)
		{
			if(int(sqrt(k))*int(sqrt(k))==k)mu[i]=0;
			else mu[i]=-mu[i];
		}
	}
	fr(k,1,n)fr(i,1,n/k)
		ans+=mu[i]*i*i*k*g[i*k];
	printf("%lld\n",ans);
	return 0;
}