/****************************************************************
	File name: 2327.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 10/30/2018, 10:51:05 AM
****************************************************************/
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
#define N 10010
int n,a[N],ans,t,b[10];
int main()
{
	n=read();b[1]=b[2]=1;b[3]=2;ans=3;
	fr(i,1,n)a[i]=read();
	t=0;
	fr(i,1,n-1)
		if(a[i]-b[t]>=0&&a[i]-b[t]<=1)
			t=(t&1)<<1|(a[i]-b[t]);
		else
		{
			ans&=2;
			break;
		}
	if(b[t]!=a[n])ans&=2;
	t=1;
	fr(i,1,n-1)
		if(a[i]-b[t]>=0&&a[i]-b[t]<=1)
			t=(t&1)<<1|(a[i]-b[t]);
		else
		{
			ans&=1;
			break;
		}
	if(b[t]!=a[n])ans&=1;
	printf("%d\n",b[ans]);
	return 0;
}