/**************************************************************
	File name: 4717.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 3/11/2019, 5:12:58 PM
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
#define N 17
#define mod 998244353
#define p2 499122177
int n;
long long C[(1<<N)+10],A[N+5][(1<<N)+10],B[N+5][(1<<N)+10],a[(1<<N)+10],b[(1<<N)+10];
void calcor(int n,long long *C,long long *a,long long *b)
{
	if(!n)
	{
		*C=*a**b%mod;
		return;
	}
	calcor(n-1,C,a,b);
	fr(i,0,(1<<(n-1))-1)
	{
		A[n-1][i]=(a[i]+a[i+(1<<(n-1))])%mod;
		B[n-1][i]=(b[i]+b[i+(1<<(n-1))])%mod;
	}
	calcor(n-1,C+(1<<(n-1)),A[n-1],B[n-1]);
	fr(i,0,(1<<(n-1))-1)
		C[i+(1<<(n-1))]=(C[i+(1<<(n-1))]-C[i]+mod)%mod;
}
void calcand(int n,long long *C,long long *a,long long *b)
{
	if(!n)
	{
		*C=*a**b%mod;
		return;
	}
	calcand(n-1,C+(1<<(n-1)),a+(1<<(n-1)),b+(1<<(n-1)));
	fr(i,0,(1<<(n-1))-1)
	{
		A[n-1][i]=(a[i]+a[i+(1<<(n-1))])%mod;
		B[n-1][i]=(b[i]+b[i+(1<<(n-1))])%mod;
	}
	calcand(n-1,C,A[n-1],B[n-1]);
	fr(i,0,(1<<(n-1))-1)
		C[i]=(C[i]-C[i+(1<<(n-1))]+mod)%mod;
}
void calcxor(int n,long long *C,long long *a,long long *b)
{
	if(!n)
	{
		*C=*a**b%mod;
		return;
	}
	fr(i,0,(1<<(n-1))-1)
	{
		A[n-1][i]=(a[i]+a[i+(1<<(n-1))])%mod;
		B[n-1][i]=(b[i]+b[i+(1<<(n-1))])%mod;
	}
	calcxor(n-1,C,A[n-1],B[n-1]);
	fr(i,0,(1<<(n-1))-1)
	{
		A[n-1][i]=(a[i]-a[i+(1<<(n-1))]+mod)%mod;
		B[n-1][i]=(b[i]-b[i+(1<<(n-1))]+mod)%mod;
	}
	calcxor(n-1,C+(1<<(n-1)),A[n-1],B[n-1]);
	fr(i,0,(1<<(n-1))-1)
	{
		long long x=C[i],y=C[i+(1<<(n-1))];
		C[i]=(x+y)*p2%mod;
		C[i+(1<<(n-1))]=(x-y+mod)*p2%mod;
	}
}
int main()
{
	n=read();
	fr(i,0,(1<<n)-1)
		a[i]=read();
	fr(i,0,(1<<n)-1)
		b[i]=read();
	memset(C,0,sizeof(C));
	calcor(n,C,a,b);
	fr(i,0,(1<<n)-1)
		printf("%lld%c",C[i],i==(1<<n)-1?'\n':' ');
	memset(C,0,sizeof(C));
	calcand(n,C,a,b);
	fr(i,0,(1<<n)-1)
		printf("%lld%c",C[i],i==(1<<n)-1?'\n':' ');
	memset(C,0,sizeof(C));
	calcxor(n,C,a,b);
	fr(i,0,(1<<n)-1)
		printf("%lld%c",C[i],i==(1<<n)-1?'\n':' ');
	return 0;
}