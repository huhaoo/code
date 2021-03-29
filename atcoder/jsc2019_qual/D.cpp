/**************************************************************
	File name: D.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/24 下午8:26:45
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
const int N=510;
int main()
{
	int n=read();
	fr(i,1,n)
		fr(j,i+1,n)
			fd(k,10,0)
				if((1<<k)&((i-1)^(j-1)))
				{
					printf("%d%c",k+1,j==n?'\n':' ');
					break;
				}
	return 0;
}