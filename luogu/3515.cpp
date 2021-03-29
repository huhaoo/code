/***************************************************************
	File name: 3515.cpp
	Author: huhao
	Create time: Thu 26 Sep 2019 08:21:00 AM CST
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
const int N=500010;
#define i64 long long
const i64 inf=1ll<<50;
i64 n,a[N],q[N],l[N],r[N],L,R,ans[N];
i64 f(i64 i,i64 j)
{
	return a[j]-a[i]+ceil(sqrt(abs(j-i)));
}
double F(i64 i,i64 j)
{
	return a[j]-a[i]+sqrt(abs(j-i));
}
int main()
{
	n=read();
	fr(i,1,n)
		a[i]=read();
	q[L=R=1]=1;
	l[1]=1;
	r[1]=n;
	fr(i,2,n)
	{
		if(L<=R)
		{
			ans[i]=max(ans[i],f(i,q[L]));
			l[L]=i+1;
		}
		if(i==r[L])
			L++;
		while(L<=R&&F(l[R],q[R])<=F(l[R],i))
			R--;
		if(L<=R)
		{
			i64 _l=l[R]+1,_r=r[R]+1;
			while(_l<_r)
			{
				i64 m=(_l+_r)>>1;
				if(F(m,q[R])<=F(m,i))
					_r=m;
				else
					_l=m+1;
			}
			r[R]=_r-1;
			R++;
			q[R]=i;
			l[R]=_r;
			r[R]=n;
		}
		else 
		{
			R++;
			q[R]=i;
			l[R]=i;
			r[R]=n;
		}
	}
	reverse(a+1,a+n+1);
	q[L=R=1]=1;
	l[1]=1;
	r[1]=n;
	fr(i,2,n)
	{
		if(L<=R)
		{
			ans[n-i+1]=max(ans[n-i+1],f(i,q[L]));
			l[L]=i+1;
		}
		if(i==r[L])
			L++;
		while(L<=R&&F(l[R],q[R])<=F(l[R],i))
			R--;
		if(L<=R)
		{
			i64 _l=l[R]+1,_r=r[R]+1;
			while(_l<_r)
			{
				i64 m=(_l+_r)>>1;
				if(F(m,q[R])<=F(m,i))
					_r=m;
				else
					_l=m+1;
			}
			r[R]=_r-1;
			R++;
			q[R]=i;
			l[R]=_r;
			r[R]=n;
		}
		else 
		{
			R++;
			q[R]=i;
			l[R]=i;
			r[R]=n;
		}
	}
	fr(i,1,n)
		printf("%lld\n",ans[i]);
	return 0;
}
