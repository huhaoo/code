/***************************************************************
	File name: 1256A.cpp
	Author: huhao
	Create time: Mon 04 Nov 2019 09:15:43 PM CST
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
int main()
{
	int q=read();
	while(q--)
	{
		int a=read(),b=read(),n=read(),S=read();
		if((long long)a*n>S)
			printf(S%n<=b?"Yes":"No");
		else
			printf(S-a*n<=b?"Yes":"No");
		putchar(10);
	}
	return 0;
}
