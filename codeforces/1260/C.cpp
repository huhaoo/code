/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2019-11-27 22:00:29
****************************************************************/
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
int main()
{
	fr(i,1,read())
	{
		int r=read(),b=read(),k=read();
		if(r<b) swap(r,b);
		printf("%s\n",(r-__gcd(r,b)+b-1)/b<k?"OBEY":"REBEL");
	}
	return 0;
}