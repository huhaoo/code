/***************************************************************
	File name: 1244E.cpp
	Author: huhao
	Create time: Sun 13 Oct 2019 05:42:33 PM CST
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
const int N=100010;
i64 n,k,a[N],l,r;
int main()
{
	n=read();
	k=read();
	fr(i,1,n)
		a[i]=read();
	sort(a+1,a+n+1);
	l=1;
	r=n;
	while(a[l]==a[l+1]&&l<n)
		l++;
	while(a[r]==a[r-1]&&r>1)
		r--;
	while(k>=min(l,n-r+1)&&l<=r)
	{
		if(l<=n-r+1)
		{
			i64 s=min(k/l,a[l+1]-a[l]);
			a[l]+=s;
			k-=l*s;
			while(a[l]==a[l+1]&&l<n)
				l++;
		}
		else
		{
			i64 s=min(k/(n-r+1),a[r]-a[r-1]);
			a[r]-=s;
			k-=(n-r+1)*s;
			while(a[r]==a[r-1]&&r>1)
				r--;
		}
	}
	printf("%d\n",int(l<r?a[r]-a[l]:0));
	return 0;
}
