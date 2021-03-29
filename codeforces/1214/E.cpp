/***************************************************************
	File name: 1214E.cpp
	Author: huhao
	Create time: Wed 04 Sep 2019 06:05:48 PM CST
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
const int N=400010;
int s[N],t,T,n,a[N],r[N],p[N];
int cmp(int x,int y)
{
	return a[x]>a[y];
}
int main()
{
	n=read();
	fr(i,1,n)
	{
		a[i]=read();
		r[i]=i;
	}
	sort(r+1,r+n+1,cmp);
	t=n;
	fr(i,1,n)
	{
		s[i]=r[i]*2-1;
		if(i+a[r[i]]>t)
		{
			t++;
			s[t]=r[i]*2;
		}
		else
			p[r[i]]=i+a[r[i]]-1;
	}
	fr(i,1,t-1)
		printf("%d %d\n",s[i],s[i+1]);
	fr(i,1,n)
		if(p[i])
			printf("%d %d\n",i*2,s[p[i]]);
	return 0;
}
