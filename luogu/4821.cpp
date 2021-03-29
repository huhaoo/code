/****************************************************************
	File name: 4821.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/21/2018, 8:30:54 PM
****************************************************************/
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
#define N 110
#define m 100
#define mod 2007
int T,p[N];
int main()
{
	p[0]=1;
	fr(i,1,m)p[i]=p[i-1]*5%mod;
	T=read();
	while(T--)
	{
		int n=read();
		printf("%d\n",n*4%mod*p[n-1]%mod);
	}
	return 0;
}