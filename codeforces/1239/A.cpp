/***************************************************************
	File name: 1239.cpp
	Author: huhao
	Create time: Sun 20 Oct 2019 05:07:50 PM CST
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
const int mod=1000000007;
const int N=200010;
int n,m,f[N],ans;
int main()
{
	n=read();
	m=read();
	f[1]=1;
	f[2]=2;
	fr(i,3,n+m)
		f[i]=(f[i-1]+f[i-2])%mod;
	printf("%d\n",int(2*(long long)(f[n]+f[m]-1)%mod));
	return 0;
}
