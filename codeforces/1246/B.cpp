/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2019-10-26 19:16:10
****************************************************************/
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#include<map>
map<long long,int>t;
const long long N=100010,inf=10000000000ll;
long long n,k,q[N],Q;
long long ans;
int power(int a,int b)
{
	int r=1;
	fr(i,1,n)
		r*=a;
	return r;
}
int main()
{
	n=read();
	k=read();
	fr(i,1,100000)
	{
		long long j=1;
		fr(l,1,k)
		{
			j=j*i;
			if(j>inf)
				break;
		}
		if(j<=inf)
			q[++Q]=j;
	}
	ans=0;
	fr(i,1,n)
	{
		long long a=read(),b=1,c=1;
		fr(j,2,Q)
		{
			if(j*j>a)
				break;
			while(a%q[j]==0)
				a/=q[j];
			long long k=1;
			while(a%j==0)
			{
				a/=j;
				k*=j;
			}
			c*=k;
			if(k>1&&b<=100000)
				b*=q[j]/k;
		}
		c*=a;
		if(b<=100000&&a<=Q)
			b*=q[a]/a;
		ans+=t[c];
		if(b<=100000)
			t[b]++;
	}
	printf("%I64d\n",ans);
	return 0;
}