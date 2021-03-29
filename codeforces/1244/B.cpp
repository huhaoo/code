/***************************************************************
	File name: 1244B.cpp
	Author: huhao
	Create time: Sun 13 Oct 2019 05:06:52 PM CST
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
const int N=100010;
int T,n,ans;
char s[N];
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		scanf("%s",s+1);
		ans=n;
		fr(i,1,n)
			if(s[i]=='1')
				ans=max(ans,max(i*2,max(n+1,(n-i+1)*2)));
		printf("%d\n",ans);
	}
	return 0;
}
