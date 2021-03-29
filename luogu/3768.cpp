/***************************************************************
	File name: 3768.cpp
	Author: huhao
	Create time: Tue 10 Sep 2019 06:07:51 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define i64 long long
#define fr(i,a,b) for(i64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(i64 i=(a),end_##i=(b);i>=end_##i;i--)
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
const i64 N=15000010,M=15000000,P=2000010;
const i64 K=1010;
i64 n,phi[N],p[P],c,mod;
i64 s[N],S[K],ans;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	while(b)
	{
		if(b&1)
			r=(i64)r*a%p;
		a=(i64)a*a%p;
		b>>=1;
	}
	return r;
}
i64 i6,i4;
i64 s2(i64 n)
{
	n%=mod;
	return n*(n+1)%mod*(2*n+1)%mod*i6%mod;
}
i64 s3(i64 n)
{
	n%=mod;
	return n*(n+1)%mod*n%mod*(n+1)%mod*i4%mod;
}
i64 s12(i64 n)
{
	return s3(n);
}
i64 calc(i64 m,i64 n)
{
	if(n<=M)
		return s[n];
	if(S[m/n]!=-1)
		return S[m/n];
	i64 &ans=S[m/n];
	ans=s3(n);
	for(i64 i=2,j;i<=n;i=j+1)
	{
		i64 k=n/i;
		j=n/k;
		ans=(ans-(s2(j)-s2(i-1)+mod)*calc(m,k))%mod+mod;
	}
	return ans%mod;
}
i64 calc(i64 n)
{
	if(n<=M)
		return s[n];
	return calc(::n,n);
}
int main()
{
	mod=read();
	n=read();
	i6=power(6,mod-2,mod);
	i4=power(4,mod-2,mod);
	phi[1]=1;
	fr(i,2,M)
	{
		if(!phi[i])
		{
			p[++c]=i;
			phi[i]=i-1;
	
		}
		fr(j,1,c)
			if(i*p[j]<=M)
			{
				if(i%p[j])
					phi[i*p[j]]=phi[i]*(p[j]-1);
				else
				{
					phi[i*p[j]]=phi[i]*p[j];
					break;
				}
			}
			else
				break;
	}
	fr(i,1,M)
		s[i]=(s[i-1]+(i64)phi[i]*i%mod*i)%mod;
	fr(i,1,n/M)
		S[i]=-1;
	for(i64 i=1,j,lst=calc(0);i<=n;i=j+1)
	{
		i64 k=n/i;
		j=n/k;
		ans=(ans+(calc(j)-lst+mod)*s12(k))%mod;
		lst=calc(j);
	}
	printf("%lld\n",ans);
	return 0;
}
