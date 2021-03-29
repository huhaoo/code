/**************************************************************
	File name: B.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/24 下午8:06:40
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
const int N=2010,mod=1000000007;
long long n,k,a[N],s[N],S[N],ans;
int main()
{
	n=read();
	k=read();
	fr(i,1,n)
	{
		a[i]=read();
		S[a[i]]++;
	}
	fr(i,1,n)
	{
		s[a[i]]++;
		fr(j,a[i]+1,2000)
			ans=(ans+k*s[j]+k*(k-1)/2%mod*S[j])%mod;
	}
	printf("%lld\n",ans);
	return 0;
}