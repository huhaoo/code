/****************************************************************
*	Author: huhao
*	Email: 826538400@qq.com
*	Create time: 2019-11-29 23:13:51
****************************************************************/
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const int N=1000010;
int a[N],b,n;
int main()
{
	int t=read();
	while(t--)
	{
		n=read();
		a[b=1]=0;
		for(int i=1;i<=n;i=n/(n/i)+1) a[++b]=n/i;
		sort(a+1,a+b+1);
		printf("%d\n",b);
		fr(i,1,b) printf("%d%c",a[i],i==b?'\n':' ');
	}
	return 0;
}