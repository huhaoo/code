/***************************************************************
	File name: 1214B.cpp
	Author: huhao
	Create time: Wed 04 Sep 2019 05:13:41 PM CST
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
int a,b,n,ans;
int main()
{
	a=read();
	b=read();
	n=read();
	fr(i,0,n)
		if(i<=a&&n-i<=b)
			ans++;
	printf("%d\n",ans);
	return 0;
}
