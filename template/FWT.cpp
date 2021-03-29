/***************************************************************
	File name: FWT.cpp
	Author: huhao
	Create time: Fri 19 Jun 2020 04:26:46 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
#define i64 long long
const int N=(1<<17)|10;
const int mod=998244353,i2=(mod+1)/2;
int n;
i64 A[N],B[N],C[N];
void fwt_or(i64 *a,int opt)
{
	fr(i,0,n-1) for(int j=0;j<(1<<n);j+=(1<<(i+1))) fr(k,0,(1<<i)-1) a[j+k+(1<<i)]=(a[j+k+(1<<i)]+a[j+k]*opt+mod)%mod;
}
void fwt_and(i64 *a,int opt)
{
	fr(i,0,n-1) for(int j=0;j<(1<<n);j+=(1<<(i+1))) fr(k,0,(1<<i)-1) a[j+k]=(a[j+k]+a[j+k+(1<<i)]*opt+mod)%mod;
}
void fwt_xor(i64 *a,int opt)
{
	fr(i,0,n-1) for(int j=0;j<(1<<n);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
	{
		i64 x=a[j+k],y=a[j+k+(1<<i)];
		a[j+k]=(x+y)*(opt==1?1:i2)%mod;
		a[j+k+(1<<i)]=(x-y+mod)*(opt==1?1:i2)%mod;
	}
}
int main()
{
	n=read();
	fr(i,0,(1<<n)-1) A[i]=read();
	fr(i,0,(1<<n)-1) B[i]=read();
	fwt_or(A,1); fwt_or(B,1);
	fr(i,0,(1<<n)-1) C[i]=A[i]*B[i]%mod;
	fwt_or(A,-1); fwt_or(B,-1); fwt_or(C,-1);
	fr(i,0,(1<<n)-1) printf("%lld%c",C[i],i==end_i?'\n':' ');
	fwt_and(A,1); fwt_and(B,1);
	fr(i,0,(1<<n)-1) C[i]=A[i]*B[i]%mod;
	fwt_and(A,-1); fwt_and(B,-1); fwt_and(C,-1);
	fr(i,0,(1<<n)-1) printf("%lld%c",C[i],i==end_i?'\n':' ');
	fwt_xor(A,1); fwt_xor(B,1);
	fr(i,0,(1<<n)-1) C[i]=A[i]*B[i]%mod;
	fwt_xor(A,-1); fwt_xor(B,-1); fwt_xor(C,-1);
	fr(i,0,(1<<n)-1) printf("%lld%c",C[i],i==end_i?'\n':' ');
	return 0;
}
