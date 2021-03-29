/***************************************************************
	File name: 1244G.cpp
	Author: huhao
	Create time: Sun 13 Oct 2019 06:33:55 PM CST
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
const int N=1000010;
i64 n,k,a[N],ans;
int main()
{
	n=read();
	k=read();
	fr(i,1,n)
	{
		a[i]=i;
		k-=i;
		ans+=i;
	}
	if(k<0)
	{
		printf("-1\n");
		return 0;
	}
	fd(i,n,1)
		if(i>n-i+1&&k)
		{
			i64 x=min(i-(n-i+1),k);
			k-=x;
			ans+=x;
			swap(a[i],a[i-x]);
		}
		else
			break;
	printf("%I64d\n",ans);
	fr(i,1,n)
		printf("%d%c",(int)i,i==n?'\n':' ');
	fr(i,1,n)
		printf("%d%c",(int)a[i],i==n?'\n':' ');
	return 0;
}
