/**************************************************************
	File name: 4999.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/5/2018, 2:50:34 PM
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
#define B 18
#define mod 1000000007
long long l,r,T,ans,p[B+10];
#define pos(i,j) ((i/p[j])%10)
int main()
{
	p[0]=1;
	fr(i,1,B)p[i]=p[i-1]*10;
	T=read();
	while(T--)
	{
		l=read()-1;r=read();ans=0;
		if(r==p[18]){ans++;r--;}
		fr(i,1,9)fr(j,0,17)
		{
			if(pos(r,j)<i)ans+=i*(r/p[j+1])*p[j];
			else if(pos(r,j)==i)ans+=i*((r/p[j+1])*p[j]+(r%p[j]+1));
			else ans+=i*(r/p[j+1]+1)*p[j];
			ans%=mod;
		}
		fr(i,1,9)fr(j,0,17)
		{
			if(pos(l,j)<i)ans-=i*(l/p[j+1])*p[j];
			else if(pos(l,j)==i)ans-=i*((l/p[j+1])*p[j]+(l%p[j]+1));
			else ans-=i*(l/p[j+1]+1)*p[j];
			ans=(ans%mod+mod)%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}