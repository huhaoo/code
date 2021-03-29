/**************************************************************
	File name: 1438.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/5/2018, 6:47:07 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define N 100010
long long n,q,b1[N],b2[N];
void add(long long *b,long long p,long long v)
{
	while(p)
	{
		b[p]+=v;
		p&=p-1;
	}
}
long long query(long long *b,long long p)
{
	long long r=0;
	while(p<=n)
	{
		r+=b[p];
		p+=p&(-p);
	}
	return r;
}
int main()
{
	n=read();q=read();
	fr(i,1,n){long long a=read();add(b1,i,a);add(b1,i-1,-a);}
	while(q--)
		if(read()==1)
		{
			long long l=read(),r=read(),k=read(),d=read();k-=l*d;
			add(b1,r,k);add(b1,l-1,-k);
			add(b2,r,d);add(b2,l-1,-d);
		}
		else
		{
			long long p=read();
			printf("%lld\n",query(b1,p)+p*query(b2,p));
		}
	return 0;
}