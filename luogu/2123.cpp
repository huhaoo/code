/***************************************************************
	File name: 2123.cpp
	Author: huhao
	Create time: Sat 21 Sep 2019 04:41:18 PM CST
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
#define i64 long long
const int N=20010;
struct node
{
	int a,b;
}a[N];
int cmp(node a,node b)
{
	return min(a.a,b.b)==min(a.b,b.a)?a.a<b.a:min(a.a,b.b)<min(a.b,b.a);
}
int T,n;
i64 ans,s;
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		fr(i,1,n)
		{
			a[i].a=read();
			a[i].b=read();
		}
		sort(a+1,a+n+1,cmp);
		ans=s=0;
		fr(i,1,n)
		{
			s+=a[i].a;
			ans=max(ans,s)+a[i].b;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
