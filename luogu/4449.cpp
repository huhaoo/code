/***************************************************************
	File name: 4449.cpp
	Author: huhao
	Create time: Fri 02 Aug 2019 08:48:49 PM CST
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
#define i64 long long
const i64 N=5000010,mod=1000000007;
i64 T,k,n,m,p[N],c,mu[N],v[N],f[N],pk[N],ans;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
int main()
{
	T=read();
	k=read();
	n=5000000;
	mu[1]=1;
	f[1]=1;
	fr(i,2,n)
	{
		if(!v[i])
		{
			p[++c]=i;
			mu[i]=-1;
			pk[i]=power(i,k,mod);
			f[i]=(-1+pk[i]+mod)%mod;
			v[i]=1;
		}
		fr(j,1,c)
			if(i*p[j]<=n)
			{
				v[i*p[j]]=1;
				if(i%p[j]==0)
				{
					mu[i*p[j]]=0;
					f[i*p[j]]=f[i]*pk[p[j]]%mod;
					break;
				}
				else
				{
					mu[i*p[j]]=-mu[i];
					f[i*p[j]]=f[i]*(pk[p[j]]-1+mod)%mod;
				}
			}
			else
				break;
	}
	fr(i,1,n)
		f[i]=(f[i]+f[i-1])%mod;
	while(T--)
	{
		n=read();
		m=read();
		if(n>m)
			swap(n,m);
		ans=0;
		for(int i=1,j;i<=n;i=j+1)
		{
			j=min(n/(n/i),m/(m/i));
			ans=(ans+(f[j]-f[i-1]+mod)*(n/i)%mod*(m/i))%mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
