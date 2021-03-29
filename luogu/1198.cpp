/**************************************************************
	File name: 1198.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 10/27/2018, 2:40:14 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
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
#define N 200010
long long m,n,d,b[N],ans;
void add(long long p,long long v)
{
	while(p)
	{
		b[p]=max(b[p],v);
		p-=p&(-p);
	}
}
long long query(long long p)
{
	long long ans=0;
	while(p<=m)
	{
		ans=max(ans,b[p]);
		p+=p&(-p);
	}
	return ans;
}
int main()
{
	m=read();d=read();
	fr(_,1,m)
	{
		char s[10];
		scanf("%s",s);
		long long k=read();
		if(*s=='A')
		{
			n++;
			add(n,((k+ans)%d+d)%d);
		}
		else
			printf("%lld\n",ans=query(n-k+1));
	}
	return 0;
}