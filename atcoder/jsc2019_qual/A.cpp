/**************************************************************
	File name: A.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/24 下午8:03:14
**************************************************************/
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
	int m=read(),d=read(),ans=0;
	fr(i,1,d)
	{
		if(i%10>=2&&i/10>=2)
			ans+=((i%10)*(i/10)<=m);
	}
	printf("%d\n",ans);
	return 0;
}