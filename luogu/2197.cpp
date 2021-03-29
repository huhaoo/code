/**************************************************************
	File name: 2197.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/8/2018, 8:42:20 AM
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
int main()
{
	fr(_,1,read())
	{
		int a=0;
		fr(i,1,read())a^=read();
		if(a==0)printf("No\n");
		else printf("Yes\n");
	}
	return 0;
}