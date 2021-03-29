/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Mon 22 Feb 2021 10:27:05 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
#include<bitset>
const int N=200010;
int n,m;
char s[N];
std::bitset<N> A,B,x,y;
int main()
{
	n=read(); m=read();
	scanf("%s",s+1);
	fr(i,1,n) B[i]=1;
	fr(i,1,n) if(s[i]=='A') A[i]=1;
	while(m--)
	{
		if(A[1]==1) A[1]=0;
		else A=(A>>1)^B;
		if(A==x) break;
		if(A==y) m%=2;
		y=x; x=A;
	}
	fr(i,1,n) putchar(A[i]==1?'A':'B');
	putchar(10);
	return 0;
}
