/***************************************************************
	File name: A.cpp
	Author: huhao
	Create time: Sun 29 Nov 2020 03:07:57 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
char c[N];
int n,p,k,x,y;
int s[N];
int main()
{
	fr(T,1,read())
	{
		n=read(); p=read(); k=read();
		scanf("%s",c+1);
		x=read(); y=read(); int ans=2000000000;
		fr(i,0,n+k) s[i]=0;
		fd(i,n,1) s[i]=s[i+k]+(c[i]=='0');
		fr(i,p,n)
		{
			ans=std::min(ans,y*(i-p)+x*s[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
