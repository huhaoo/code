/**************************************************************
	File name: E.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/17 下午9:24:40
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
const int N=200010;
int n,k,f[N];
int cmp(char *a,char *b,int k)//[a<b]
{
	fr(i,0,k-1)
		if(*(a+i)!=*(b+i))
			return *(a+i)<*(b+i);
	return 0;
}
char s[N];
int main()
{
	n=read();
	k=read();
	scanf("%s",s+1);
	fr(i,1,n)
		s[n+n-i+1]=s[i];
	if(k==1)
	{
		int ans=1;
		fr(i,2,n+1)
			if(cmp(s+i,s+ans,n))
				ans=i;
		fr(i,0,n-1)
			putchar(s[ans+i]);
		putchar(10);
		return 0;
	}
	char m='z';
	int M=0;
	int p=0;
	fr(i,1,n+n)
		m=min(m,s[i]);
	fr(i,1,n+n)
		if(s[i]==m)
			M=max(M,f[i]=f[i-1]+1);
	int _m=M;
	fr(i,2,k)
	{
		M=M*2;
		if(M>=n)
		{
			fr(i,1,n)
				putchar(m);
			putchar(10);
			return 0;
		}
	}
	fr(i,n,n+n)
		if(f[i]==_m)
		{
			if(!p||cmp(s+n+n+1-(i-_m),s+p,n-M))
				p=n+n+1-(i-_m);
		}
	fr(i,1,M)
		putchar(m);
	fr(i,1,n-M)
		putchar(s[p+i-1]);
	putchar(10);
//	fr(i,1,n+n)
//		printf("%d%c",f[i],i==n+n?'\n':' ');
//	printf("%d %d\n",M,p);
	return 0;
}