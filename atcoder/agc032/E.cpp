/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Thu 16 Jan 2020 05:17:21 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
int n,a[N],m,ans,Ans;
int main()
{
	n=read()*2; m=read();
	fr(i,1,n) a[i]=read();
	std::sort(a+1,a+n+1);
	Ans=n/2;
	fd(i,n,1) while(n-i+1<=Ans&&a[i]+a[(n-Ans)-(i-(n-Ans+1))]<m) Ans--;
	int p1=n-Ans,p2=n-Ans+1;
	fr(i,1,Ans)
	{
//		printf("%d %d\n",a[p1],a[p2]);
		ans=std::max(ans,(a[p1--]+a[p2++])%m);
	}
	p1=n/2-Ans; p2=n/2-Ans+1;
	fr(i,1,n/2-Ans)
	{
//		printf("%d %d\n",a[p1],a[p2]);
		ans=std::max(ans,(a[p1--]+a[p2++])%m);
	}
	printf("%d\n",ans);
	return 0;
}
