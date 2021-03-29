/***************************************************************
	File name: 1256E.cpp
	Author: huhao
	Create time: Mon 04 Nov 2019 09:38:31 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define i64 long long
#define fr(i,a,b) for(i64 i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(i64 i=(a),end_##i=(b);i>=end_##i;i--)
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
const i64 inf=1ll<<50;
i64	n,f[N],m,pre[N],Pre,ans[N],c,s[N];
pair<i64,i64> a[N];
int main()
{
	n=read();
	fr(i,1,n)
	{
		a[i].first=read();
		a[i].second=i;
	}
	sort(a+1,a+n+1);
	m=-a[1].first;
	f[1]=f[2]=inf;
	fr(i,3,n)
	{
		f[i]=m+a[i].first;
		pre[i]=Pre;
		if(m>f[i-2]-a[i-1].first)
		{
			m=f[i-2]-a[i-1].first;
			Pre=i-2;
		}
	}
	int k=n;
	while(k)
	{
		ans[++c]=k;
		k=pre[k];
	}
	fr(i,1,c)
		fr(j,ans[i+1]+1,ans[i])
			s[a[j].second]=i;
	printf("%I64d %d\n",f[n],int(c));
	fr(i,1,n)
		printf("%d%c",int(s[i]),i==n?'\n':' ');
	return 0;
}
