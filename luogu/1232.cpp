/***************************************************************
	File name: 1232.cpp
	Author: huhao
	Create time: Tue 11 Jun 2019 04:50:46 PM CST
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
const int N=200010;
int n,a[N],b[N],c[N],d[N],s[N];
double ans;
int main()
{
	n=read();
	ans=2;
	s[1]=1;
	s[2]=-1;
	fr(i,1,n)
	{
		d[i]=read();
		c[d[i]]=i;
	}
	fr(i,1,n)
	{
		b[i]=read();
		a[b[i]]=i;
	}
	fr(i,1,n)
	{
		d[i]=a[d[i]];
		b[i]=c[b[i]];
	}
	fr(i,1,n-1)
		if(b[i]>b[i+1])
			ans=ans+1;
	fr(i,1,n)
		if(d[i]+1<d[i+1])
		{
			s[d[i]]++;
			s[d[i+1]]--;
		}
	fr(i,1,n-1)
	{
		s[i]+=s[i-1];
		if(!s[i])
			ans+=0.5;
	}
	printf("%.3lf\n",ans);
	return 0;
}
