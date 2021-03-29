/***************************************************************
	File name: C.cpp
	Author: huhao
	Create time: Sun 04 Aug 2019 08:05:06 PM CST
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
const int N=100010;
int n,ans,a[N];
int main()
{
	ans=1;
	n=read();
	fr(i,1,n)
	{
		a[i]=read();
	}
	fd(i,n-1,1)
	{
		if(a[i]>a[i+1])
			a[i]--;
		if(a[i]>a[i+1])
			ans=0;
	}
	printf("%s\n",ans?"Yes":"No");
	return 0;
}
