/***************************************************************
	File name: exkmp.cpp
	Author: huhao
	Create time: Fri 15 Nov 2019 03:00:59 PM CST
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
const int N=200010;
int n,m,f[N],z[N];
char s[N],c[N];
int main()
{
	scanf("%s%s",c+1,s+1);
	n=strlen(s+1); m=strlen(c+1);
	memcpy(s+n+2,c+1,m*sizeof(char));
	for(int i=2,l=0,r=0;i<=n+m+1;i++)
	{
		if(i<=r) f[i]=min(r-i+1,f[i-l+1]);
		while(i+f[i]<=n+m+1&&s[i+f[i]]==s[1+f[i]]) f[i]++;
		r=max(r,i+f[i]-1);
	}
	f[1]=n;
	fr(i,1,n) printf("%d%c",f[i],i==n?'\n':' ');
	fr(i,1,m) printf("%d%c",f[i+n+1],i==m?'\n':' ');
	return 0;
}
