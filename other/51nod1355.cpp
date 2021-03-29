/***************************************************************
	File name: 51nod1355.cpp
	Author: huhao
	Create time: Tue 14 Jan 2020 04:51:54 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
#define i64 long long
const int N=1000010,mod=1000000007;
i64 n,h[N],a[N],g[N],f[N],mu[N],p[N],c,v[N],ans;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	while(b)
	{
		if(b&1) r=r*a%p;
		a=a*a%p; b>>=1;
	}
	return r;
}
int main()
{
	n=read(); a[1]=a[2]=1;
	fr(i,1,n) h[read()]=1;
	n=1000000; mu[1]=1; ans=1;
	fr(i,2,n)
	{
		if(!v[i]){ p[++c]=i; mu[i]=-1; }
		fr(j,1,c)
			if(i*p[j]<=n)
			{
				v[i*p[j]]=1;
				if(i%p[j]==0){ mu[i*p[j]]=0; break; }
				else mu[i*p[j]]=-mu[i];
			}
			else break;
	}
	fr(i,3,n) a[i]=(a[i-1]+a[i-2])%mod;
	fr(i,1,n) fr(j,1,n/i) g[i]+=h[i*j];
	fr(i,1,n) g[i]=(g[i]>0);
	fr(i,1,n) fr(j,1,n/i) f[i]+=g[i*j]*mu[j];
	fr(i,1,n) ans=ans*power(a[i],mod-1+f[i],mod)%mod;
	printf("%lld\n",(ans%mod+mod)%mod);
	return 0;
}
