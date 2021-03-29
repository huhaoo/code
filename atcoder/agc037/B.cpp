/**************************************************************
	File name: B.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/17 下午8:31:08
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
const int N=300010,mod=998244353;
char s[N];
int a[N],x,y,X,Y,n;
long long ans=1;
int main()
{
	n=read()*3;
	scanf("%s",s+1);
	x=1;
	y=2;
	fr(i,1,n)
	{
		s[i]=s[i]=='G'?1:(s[i]=='R'?2:3);
		if(s[i]==x)
			X++;
		else if(s[i]==y)
		{
			if(X!=Y)
			{
				ans=ans*(X-Y)%mod;
				Y++;
			}
			else
			{
				swap(x,y);
				X++;
			}
		}
		else
		{
			if(Y)
			{
				ans=ans*Y%mod;
				Y--;
				X--;
			}
			else if(X)
			{
				y=s[i];
				Y++;
				ans=ans*X%mod;
			}
			else
			{
				x=s[i];
				X++;
			}
		}
	}
	fr(i,1,n/3)
		ans=ans*i%mod;
	printf("%lld\n",ans);
	return 0;
}