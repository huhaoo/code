/**************************************************************
	File name: 2714.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/12/2018, 1:59:02 PM
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
#define N 10010
long long n,a,mu[N],s[N],ans,m=10000;
int main()
{
	mu[1]=1;
	fr(i,2,m)
	{
		mu[i]=-1;
		fr(j,2,sqrt(i))
			if(i%j==0)
			{
				int k=i;
				while(k%j==0)k/=j;
				if(k*j!=i)mu[i]=0;
				else mu[i]=-mu[k];
				break;
			}
	}
	while(scanf("%lld",&n)!=EOF)
	{
		fr(i,1,m)s[i]=0;
		fr(i,1,n)
		{
			a=read();
			fr(j,1,sqrt(a))
				if(a%j==0)
				{
					if(j*j==a)s[j]++;
					else{s[j]++;s[a/j]++;}
				}
		}
		ans=0;
		fr(i,1,m)ans+=mu[i]*s[i]*(s[i]-1)*(s[i]-2)*(s[i]-3)/24;
		printf("%lld\n",ans);
	}
	return 0;
}