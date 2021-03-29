/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Sat 28 Nov 2020 02:17:51 PM CST
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
int n,a[N];
int main()
{
	read(); n=read();
	fr(i,1,n) a[i]=read();
	if(n==1)
	{
		if(a[1]==1) printf("1\n1\n1\n");
		else printf("%d\n2\n1 %d\n",a[1],a[1]-1);
		return 0;
	}
	fr(i,2,n-1) if(a[i]&1)
	{
		if(a[1]&1)
		{
			if(a[n]&1){ printf("Impossible\n"); return 0; }
			std::swap(a[i],a[n]);
		}
		else std::swap(a[i],a[1]);
	}
	fr(i,1,n) printf("%d%c",a[i],i==n?'\n':' ');
	a[1]--; a[n]++;
	printf("%d\n",n-(a[1]==0));
	fr(i,1,n) if(a[i]) printf("%d%c",a[i],i==n?'\n':' ');
	return 0;
}
