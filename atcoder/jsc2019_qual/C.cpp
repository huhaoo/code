/**************************************************************
	File name: C.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/24 下午8:17:08
**************************************************************/
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
const int N=200010,mod=1000000007;
int n,t;
long long ans;
char s[N];
int main()
{
	n=read();
	scanf("%s",s+1);
	ans=1;
	fr(i,1,n*2)
		s[i]=s[i]=='B';
	fr(i,1,n)
		ans=ans*i%mod;
	fr(i,1,n*2)
	{
		s[i]=(s[i]^t)&1;
		if(s[i])
			t++;
		else
		{
			ans=ans*t%mod;
			t--;
			if(t<0)
			{
				printf("0\n");
				return 0;
			}
		}
	}
	printf("%lld\n",t==0?ans:0);
	return 0;
}