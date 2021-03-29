/***************************************************************
	File name: 5325.cpp
	Author: huhao
	Create time: Wed 26 Jun 2019 08:39:01 PM CST
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
const int N=400010,mod=1000000007;
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
i64 inv2=power(2,mod-2,mod),inv6=power(6,mod-2,mod);
i64 n,s,_n,s1[N],s2[N],w1[N],w2[N],p[N],c[N],t[N],t1[N],t2[N];
i64 id(i64 j)
{
	if(j<=s)
		return t1[j];
	return t2[n/j];
}
i64 dfs(i64 m,i64 i)
{
	if(p[i]>m)
		return 0;
	i64 k=id(m);
	i64 r=(s2[k]-s1[k]-w2[i-1]+w1[i-1]+2*mod)%mod;
	fr(j,i,_n)
	{
		if(p[j]*p[j]>m)
			break;
		for(i64 pc=p[j];pc*p[j]<=m;pc*=p[j])
		{
			i64 c=pc%mod;
			r=(r+c*(c-1)%mod*dfs(m/pc,j+1))%mod;
			c=pc*p[j]%mod;
			r=(r+c*(c-1))%mod;
		}
	}
	return r;
}
int main()
{
	n=read();
	s=sqrt(n);
	fr(i,2,s)
	{
		if(!c[i])
		{
			p[++_n]=i;
			w1[_n]=(w1[_n-1]+i)%mod;
			w2[_n]=(w2[_n-1]+i*i)%mod;
		}
		fr(j,1,_n)
		{
			if(i*p[j]>s)
				break;
			c[i*p[j]]=1;
			if(i%p[j]==0)
				break;
		}
	}
	for(i64 i=1,j;i<=n;i=j+1)
	{
		j=n/i;
		t[++t[0]]=j;
		if(j<=s)
			t1[j]=t[0];
		else
			t2[n/j]=t[0];
		i64 k=j%mod;
		s1[t[0]]=(k*(k+1)%mod*inv2-1+mod)%mod;
		s2[t[0]]=(k*(k+1)%mod*(2*k+1)%mod*inv6-1+mod)%mod;
		j=n/j;
	}
	fr(i,1,_n)
		fr(j,1,t[0])
		{
			if(p[i]*p[i]>t[j])
				break;
			i64 k=id(t[j]/p[i]);
			s1[j]=(s1[j]-p[i]*(s1[k]-w1[i-1]+mod)%mod+mod)%mod;
			s2[j]=(s2[j]-p[i]*p[i]%mod*(s2[k]-w2[i-1]+mod)%mod+mod)%mod;
		}
	printf("%lld\n",(dfs(n,1)+1)%mod);
	return 0;
}
