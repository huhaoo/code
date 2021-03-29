/***************************************************************
	File name: distribution.cpp
	Author: huhao
	Create time: Mon 26 Oct 2020 09:54:01 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
const int N=110;
int n=59,m=37;
i64 p2[N],p3[N];
int main()
{
	freopen("distribution.in","r",stdin); freopen("distribution.out","w",stdout);
	p2[0]=p3[0]=1;
	fr(i,1,n+1) p2[i]=p2[i-1]*2;
	fr(i,1,m+1) p3[i]=p3[i-1]*3;
	fr(T,1,read())
	{
		i64 v=read();
		i64 s[N],t; t=0;
		fr(i,0,m)
		{
			int mx=-1;
			fr(j,0,n)
				if(v>=p3[i]*p2[j])
				{
					if((v-p3[i]*p2[j])%p3[i+1]==0) mx=j;
				}
				else break;
			if(mx>=0){ s[++t]=p3[i]*p2[mx]; v-=s[t]; }
		}
		printf("%lld\n",t);
		fr(i,1,t) printf("%lld%c",s[i],i==t?'\n':' ');
	}
	return 0;
}
