/***************************************************************
	File name: 1244A.cpp
	Author: huhao
	Create time: Sun 13 Oct 2019 05:10:26 PM CST
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
int T,a,b,c,d,n;
int main()
{
	T=read();
	while(T--)
	{
		a=read();
		b=read();
		c=read();
		d=read();
		n=read();
		if((a+c-1)/c+(b+d-1)/d<=n)
			printf("%d %d\n",(a+c-1)/c,n-(a+c-1)/c);
		else
			printf("-1\n");
	}
	return 0;
}
