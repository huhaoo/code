/***************************************************************
	File name: 3266.cpp
	Author: huhao
	Create time: Wed 07 Aug 2019 07:12:32 PM CST
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
const int N=3000010,mod=1000000007;
int fac[N+10],inv[N+10],n,m,x,y,ans;
int power(int a,int b,int p)
{
	int r=1;
	while(b)
	{
		if(b&1)
			r=1ll*r*a%p;
		a=1ll*a*a%p;
		b>>=1;
	}
	return r;
}
int C(int a,int b)
{
	if(a<0||b<0||b>a)
		return 0;
	return 1ll*fac[a]*inv[b]%mod*inv[a-b]%mod;
}
int main()
{
	n=read();
	m=read();
	fac[0]=1;
	fr(i,1,N)
		fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=power(fac[N],mod-2,mod);
	fd(i,N,1)
		inv[i-1]=1ll*inv[i]*i%mod;
	x=n+m+1;
	y=n;
	ans=C(x+y,y);
	while(x>=0&&y>=0)
	{
		swap(x,y);
		x--;
		y++;
		ans=(ans-C(x+y,y)+mod)%mod;
		swap(x,y);
		x+=m+2;
		y-=m+2;
		ans=(ans+C(x+y,y))%mod;
	}
	x=n+m+1;
	y=n;
	while(x>=0&&y>=0)
	{
		swap(x,y);
		x+=m+2;
		y-=m+2;
		ans=(ans-C(x+y,y)+mod)%mod;
		swap(x,y);
		x--;
		y++;
		ans=(ans+C(x+y,y))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
