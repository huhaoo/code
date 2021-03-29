/***************************************************************
	File name: 3210.cpp
	Author: huhao
	Create time: Tue 17 Sep 2019 03:49:49 PM CST
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
const int N=1000010;
const i64 inf=1ll<<50;
i64 n,a[N],s,p,ans,opt,b[N],m;
int main()
{
	fr(i,1,read())
	{
		i64 A=read();
		s+=A;
		a[++n]=A;
		while(n>2&&a[n]&&a[n-1]&&a[n-2]&&a[n-1]>=a[n-2]&&a[n-1]>=a[n])
		{
			n-=2;
			a[n]=a[n]+a[n+2]-a[n+1];
		}
	}
	for(i64 i=1;a[i]&&a[i+1]&&a[i]>=a[i+1];i+=2)
	{
		p+=a[i+1]-a[i];
		a[i]=a[i+1]=0;
	}
	for(i64 i=n;a[i]&&a[i-1]&&a[i]>=a[i-1];i-=2)
	{
		p+=a[i-1]-a[i];
		a[i]=a[i-1]=0;
	}
	opt=1;
	fr(i,1,n)
		if(a[i])
			b[++m]=a[i];
	sort(b+1,b+m+1);
	while(m)
	{
		ans+=opt*b[m];
		opt=-opt;
		m--;
	}
	ans+=opt*p;
	printf("%lld %lld\n",(s+ans)/2,(s-ans)/2);
	return 0;
}
