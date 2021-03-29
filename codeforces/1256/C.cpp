/***************************************************************
	File name: 1256C.cpp
	Author: huhao
	Create time: Mon 04 Nov 2019 09:28:00 PM CST
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
const int N=1010;
int n,m,d,a[N],s[N],p,ans[N],lst;
int main()
{
	n=read();
	m=read();
	d=read();
	fr(i,1,m)
		a[i]=read();
	fd(i,m,1)
		s[i]=s[i+1]+a[i];
	fr(i,1,m)
	{
		while(p-lst<d&&n-p+1>s[i])
			p++;
		p=p+a[i];
		lst=p-1;
		fr(j,1,a[i])
			ans[p-j]=i;
	}
	if(n+1-lst<=d)
	{
		printf("Yes\n");
		fr(i,1,n)
			printf("%d%c",ans[i],i==n?'\n':' ');
	}
	else
		printf("No\n");
	return 0;
}
