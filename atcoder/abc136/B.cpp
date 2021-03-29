/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Sun 04 Aug 2019 08:02:10 PM CST
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
int n,ans;
int main()
{
	n=read();
	fr(i,1,n)
	{
		if(int(log10(i))%2==0)
			ans++;
	}
	printf("%d\n",ans);
	return 0;
}
