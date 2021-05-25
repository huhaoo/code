/***************************************************************
	File name: a.cpp
	Author: huhao
	Create time: Sun 28 Mar 2021 04:25:52 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<sys/time.h>
#include<unistd.h>
#define i64 long long
#define fr(i,a,b) for(i64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(i64 i=(a),end_##i=(b);i>=end_##i;i--)
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
#define pii std::pair<i64,i64>
void exgcd(i64 a,i64 b,i64 &x,i64 &y)
{
	if(!b){ x=1; y=0; return ; }
	exgcd(b,a%b,y,x); y-=(a/b)*x;
}
i64 inv(i64 a,i64 p)
{
	i64 x,y; exgcd(a%p,p,x,y);
	return (x%p+p)%p;
}
pii Check(i64 g,i64 a,i64 b)
{
	fr(i,0,g-1) if((i*i%g*i+b)%g==0&&((i+a)*(i+a)%g*(i+a)+b)%g==0) return {g,-i};
	return {-1,-1};
}
pii check(i64 g,i64 a,i64 b)
{
	if(3*a%g==0&&a*a%g*a%g==0)
	{
		fr(i,0,g-1) if((i*i*i+b)%g==0) return {g,-i};
		return {-1,-1};
	}
	i64 G=std::__gcd(g,a),p=g/G;
	i64 ans,t;
	if(p%3==0)
	{
		if(a%3==0){ ans=-1; t=a*a/3%p; p/=3; G*=3; }
		else return {-1,-1};
	}
	else{ ans=-1; t=inv(3,p)*a%p*a%p; }
	fr(i,0,G-1)
	{
		i64 t0=t+i*p;
		i64 u=((a*a-t0)%g+g)%g,v=((-a*t0-b)%g+g)%g;
		i64 o=std::__gcd(u,g);
		if(v%o!=0) continue;
		i64 n0=inv(u/o,g/o)*(v/o)%(g/o),n1=g/o;
		fr(i,0,o-1)
		{
			i64 Ans=n0+n1*i;
			if((Ans*Ans+Ans*a+t0)%g!=0) continue;
			if(ans==-1||Ans<ans) ans=Ans;
		}
	}
	return ans>=0?pii{g,-ans}:pii{-1,-1};
}
i64 solve(i64 a,i64 b)
{
	i64 s=a*a*a*a*a*a*a+27*a*b*b;
	pii ans={-1,-1};
	fr(i,1,sqrt(s)) if(s%i==0)
	{
		ans=std::max(ans,check(i,a,b));
		ans=std::max(ans,check(s/i,a,b));
	}
	printf("%lld %lld  %lld %lld\n",a,b,ans.first,-ans.second);
	return -ans.second;
}
int main()
{
	i64 ans=0; i64 mx=0;
	fr(i,1,2) fr(j,1,2)
	{
//		timeval time; gettimeofday(&time, NULL);
//		i64 st=(time.tv_sec*1000000 + time.tv_usec);
		ans+=solve(i,j);
//		gettimeofday(&time, NULL);
//		i64 ed=(time.tv_sec*1000000 + time.tv_usec);
//		mx=std::max(ed-st,mx);
	}
	printf("%lld\n",ans);
//	printf("Max: %lld us\n",mx);
	return 0;
}
