/***************************************************************
	File name: 3978.cpp
	Author: huhao
	Create time: Thu 02 May 2019 04:22:22 PM CST
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
double n;
int main()
{
	n=read()*1.;
	printf("%.9lf\n",n*(n+1)/2/(2*n-1));
	return 0;
}
