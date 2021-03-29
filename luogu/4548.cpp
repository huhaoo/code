/***************************************************************
	File name: 4548.cpp
	Author: huhao
	Create time: Wed 07 Aug 2019 01:55:12 PM CST
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
const int N=100010,mod=10000;
int n,t,f[N],k,a[N],p[N],m,ans;
int main()
{
	n=read();
	t=read();
	p[0]=1;
	fr(i,1,100000)
		p[i]=p[i-1]*n%mod;
	while(t--)
	{
		m=read();
		fr(i,1,m)
			a[i]=read();
		k=0;
		fr(i,2,m)
		{
			while(a[i]!=a[k+1]&&k)
				k=f[k];
			if(a[i]==a[k+1])
				k++;
			f[i]=k;
		}
		k=m;
		ans=0;
		while(k)
		{
			ans=(ans+p[k])%mod;
			k=f[k];
		}
		printf("%d%d%d%d\n",ans/1000%10,ans/100%10,ans/10%10,ans%10);
	}
	return 0;
}
