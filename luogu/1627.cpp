/**************************************************************
	File name: 1627.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/11/2018, 4:25:45 PM
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
#define N 200010
int las,s[N],n,b,a[N],p;
long long ans;
int main()
{
	n=read();b=read();
	fr(i,1,n)
	{
		a[i]=read();
		if(a[i]>b)a[i]=1;
		else if(a[i]<b)a[i]=-1;
		else a[i]=0,p=i;
	}
	fd(i,p,1)s[n+(las+=a[i])]++;
	las=0;
	fr(i,p,n)ans+=s[-(las+=a[i])+n];
	printf("%lld\n",ans);
	return 0;
}