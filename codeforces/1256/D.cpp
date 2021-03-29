/***************************************************************
	File name: 1256D.cpp
	Author: huhao
	Create time: Mon 04 Nov 2019 09:33:44 PM CST
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
i64 q;
i64 n,k;
char s[N],ans[N];
i64 a[N],c;
int main()
{
	q=read();
	while(q--)
	{
		n=read();
		k=read();
		scanf("%s",s+1);
		fr(i,1,n)
			ans[i]='1';
		ans[n+1]=0;
		c=0;
		fr(i,1,n)
			if(s[i]=='0')
				a[++c]=i;
		fr(i,1,c)
			if(k>a[i]-i)
			{
				k-=a[i]-i;
				a[i]=i;
			}
			else
			{
				a[i]-=k;
				break;
			}
		fr(i,1,c)
			ans[a[i]]='0';
		printf("%s\n",ans+1);
	}
	return 0;
}
