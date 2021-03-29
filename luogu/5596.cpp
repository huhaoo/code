/***************************************************************
	File name: a.cpp
	Author: huhao
	Create time: Sun 20 Oct 2019 02:11:04 PM CST
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
i64 a,b,ans,A;
void solve(i64 i,i64 opt)
{
	i64 y=0,u=0;
	if(opt)
	{
		if((i+A/i)%4==0)
			y=(i+A/i)/4;
		else
			return;
		u=(A/i-i)/2;
	}
	else
	{
		if((A/i-i)%4==0)
			y=(A/i-i)/4;
		else
			return;
		u=(i+A/i)/2;
	}
	if(y>=0&&a%2==u%2&&-a+u>=0)
		ans++;
}
int main()
{
	a=read();
	b=read();
	A=a*a-4*b;
	if(!A)
	{
		printf("inf\n");
		return 0;
	}
	int opt=0;
	if(A<0)
	{
		A=-A;
		opt=1;
	}
	fr(i,1,sqrt(A))
		if(A%i==0)
		{
			if(i*i!=A)
				solve(A/i,opt);
			solve(i,opt);
		}
	printf("%lld\n",ans);
	return 0;
}
