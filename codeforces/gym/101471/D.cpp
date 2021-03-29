/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Mon 30 Nov 2020 09:29:53 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
#define pii std::pair<i64,i64>
#define F first
#define S second
const int N=500010;
int n,m; i64 ans;
pii a[N],b[N];
pii s[N]; int t;
pii A,B;
i64 calc(pii a,pii b)
{
	return b.F>=a.F?(b.F-a.F)*(a.S-b.S):0;
}
bool cmp(pii a,pii b,i64 p,i64 q)
{
//	assert(a.F<=b.F);
	if(p<=b.F) return 1;
	return a.S-q/(p-a.F)>=b.S-q/(p-b.F);
}
bool check(pii a,pii b,pii c,i64 q)
{
/*	i64 l=1,r=1ll<<60;
	while(l<r)
	{
		i64 mid=(l+r)>>1;
		if(cmp(b,c,mid,q)) l=mid+1;
		else r=mid;
	}
	l--;
	return cmp(a,b,l,q);*/
	i64 x1=b.F,x2=c.F,y1=b.S,y2=c.S;
	i64 p=(-x1*y1-x2*y1+x1*y2+x2*y2+sqrt(x2-x1)*sqrt(y2-y1)*sqrt(4*q+x1*y1-x2*y1-x1*y2+x2*y2))/(2*(y2-y1));
	if(!cmp(b,c,p,q)) p--;
//	printf("%lld %lld  %lld %lld  %lld   %lld %lld  %d\n",x1,y1,x2,y2,q,l,p,cmp(b,c,p,q));
	return cmp(a,b,p,q);
}
bool check(i64 q)
{
//	fprintf(stderr,"%lld\n",q);
	t=0;
	fr(i,1,n) if(!t||!cmp(s[t],a[i],1ll<<60,q))
	{
		while(t>=2&&check(s[t-1],s[t],a[i],q)) t--;
		s[++t]=a[i];
	}
//	fr(i,1,t) printf("(%lld,%lld)%c",s[i].F,1000000001-s[i].S,i==t?'\n':' ');
	fd(i,m,1)
	{
//		printf("< %lld %lld  %lld",s[t-1].F,s[t].F,b[i].F); fflush(stdout);
		while(t>=2&&cmp(s[t-1],s[t],b[i].F,q)) t--;
		ans=std::max(ans,calc(s[t],b[i]));
//		printf(">"); fflush(stdout);
		if(calc(s[t],b[i])>=q)
		{
			A=s[t]; B=b[i];
//			printf("%lld %lld  %lld %lld    %lld/%lld\n",s[t].F,1000000001-s[t].S,b[i].F,1000000001-b[i].S,q,calc(s[t],b[i]));
			return 1;
		}
	}
	return 0;
}
int main()
{
	n=read(); m=read();
	fr(i,1,n){ a[i].F=read(); a[i].S=1000000001-read(); }
	fr(i,1,m){ b[i].F=read(); b[i].S=1000000001-read(); }
	std::sort(a+1,a+n+1); std::sort(b+1,b+m+1);
	i64 l=1,r=1ll<<60;
	while(l<r)
	{
		i64 mid=(l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid;
	}
	int _a=0,_b=0;
	fr(i,1,n) if(a[i]==A) _a=i;
	fr(i,1,m) if(b[i]==B) _b=i;
	fr(i,std::max(1,_a-1000),std::min(n,_a+1000)) fr(j,std::max(1,_b-1000),std::min(m,_b+1000))
	{
/*		if(calc(a[i],b[j])>ans)
		{
			printf("%d %d   %d %d\n",_a,_b,i,j);
		}*/
		ans=std::max(ans,calc(a[i],b[j]));
	}
	printf("%lld\n",ans);
	return 0;
}
