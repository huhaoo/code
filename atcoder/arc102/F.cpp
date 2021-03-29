/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Sun 07 Jun 2020 02:34:32 PM CST
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
const int N=300010;
int n,p[N];
int check(int l,int r)
{
	fr(i,l,r) if(p[i]<l||p[i]>r) return 0;
	int lst=0;
	for(int i=l;i<=r;i+=2) if(p[i]<=i)
	{
		if(p[i]<lst) return 0;
		lst=p[i];
	}
	lst=0;
	for(int i=l;i<=r;i+=2) if(p[i]>=i)
	{
		if(p[i]<lst) return 0;
		lst=p[i];
	}
	return 1;
}
int main()
{
	n=read();
	fr(i,1,n) p[i]=read();
	for(int l=1,r=1;r<=n;l=++r)
	{
		if(p[r]==r) continue;
		while(r+2<=n&&p[r+1]==r+1&&p[r+2]!=r+2) r+=2;
		if(!check(l,r)){ printf("No\n"); return 0; }
	}
	printf("Yes\n");
	return 0;
}
