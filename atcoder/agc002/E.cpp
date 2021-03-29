/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Sun 29 Nov 2020 02:46:04 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
const int N=100010;
int n,a[N],ans,Ans;
int main()
{
	n=read();
	fr(i,1,n) a[i]=read();
	std::sort(a+1,a+n+1,[](int x,int y){ return x>y; });
	int i=1,j;
	while(a[i]>=i) i++;
	i--; j=i;
	Ans=(a[i]-i)&1;
	while(j<n&&a[j+1]==i){ j++; ans^=1; }
	printf("%s\n",ans||Ans?"First":"Second");
	return 0;
}
