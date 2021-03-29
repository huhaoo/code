/***************************************************************
	File name: PollardRho.cpp
	Author: huhao
	Create time: Fri 19 Jun 2020 09:15:29 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
#include<stdlib.h>
i64 Mod(i64 a,i64 p){ return a>=p?a-p:a; }
i64 mul(i64 a,i64 b,i64 p)
{
	i64 r=0;
	for(;b;b>>=1,a=Mod(a+a,p)) if(b&1) r=Mod(r+a,p);
	return r;
}
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=mul(a,a,p)) if(b&1) r=mul(r,a,p);
	return r;
}
i64 Check(i64 a,i64 p)
{
	i64 x=p-1,y=0;
	while(!(x&1)){ x>>=1; y++; }
	i64 v=power(a,x,p);
	if(v==1) return 1;
	while(y--)
	{
		i64 V=mul(v,v,p);
		if(V==1) return v==p-1;
		v=V;
	}
	return 0;
}
i64 check(i64 p)
{
	if(p==1) return 0;
	fr(i,1,20) if(!Check(rand()%(p-1)+1,p)) return 0;
	return 1;
}
i64 s[100],t;
i64 gcd(i64 a,i64 b){ return b?gcd(b,a%b):a; }
i64 calc(i64 n)
{
	i64 a=rand()%n;
#define f(x) Mod(mul(x,x,n)+a,n)
	i64 x=0;
	fr(i,1,20)
	{
		i64 y=x,g=1;
		fr(j,1,(1<<i))
		{
			y=f(y); g=mul(g,std::abs(y-x),n);
			if(j==end_j||j%64==0)
			{
				if(gcd(g,n)!=1) return gcd(g,n);
				g=1;
			}
		}
		x=y;
	}
	return 1;
}
void solve(i64 n)
{
	if(n==1) return ;
	if(check(n)){ s[++t]=n; return ; }
	i64 m=calc(n);
	solve(m); solve(n/m);
}
int main()
{
	srand(998244353);
	fr(T,1,read())
	{
		i64 n=read(); t=0;
		solve(n);
		if(t==1){ printf("Prime\n"); continue; }
		i64 ans=0;
		fr(i,1,t) ans=std::max(ans,s[i]);
		printf("%lld\n",ans);
	}
	return 0;
}
