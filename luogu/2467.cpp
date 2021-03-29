/**************************************************************
	File name: 2467.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/6/2018, 7:40:19 PM
**************************************************************/
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
#define N 4210
int n,p,c[N][N];
long long f[N];
int main()
{
	n=read();p=read();
	fr(i,0,n)c[i][i]=c[i][0]=1;
	fr(i,2,n)fr(j,1,i-1)c[i][j]=(c[i-1][j]+c[i-1][j-1])%p;
	f[0]=1;
	fr(i,1,n)
		for(int j=1;j<=i;j+=2)f[i]=(f[i]+f[j-1]*f[i-j]%p*c[i-1][j-1])%p;
	printf("%lld\n",2*f[n]%p);
	return 0;
}