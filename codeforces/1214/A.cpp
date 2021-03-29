/***************************************************************
	File name: 1214A.cpp
	Author: huhao
	Create time: Wed 04 Sep 2019 05:04:39 PM CST
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
const int N=1000010;
int f[N],a,b,n,ans;
int main()
{
	n=read();
	a=read();
	b=read()*5;
	ans=n;
	fr(i,0,n/a)
		ans=min(ans,(n-i*a)%b);
	printf("%d\n",ans);
	return 0;
}
