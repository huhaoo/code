/**************************************************************
	File name: a.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/17 下午8:02:06
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
const int N=200010,inf=300000;
int f[N][10],n;
char s[N];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	f[1][2]=-inf;
	f[1][1]=f[2][2]=1;
	if(s[1]==s[2])
		f[2][1]=-inf;
	else
		f[2][1]=2;
	fr(i,3,n)
	{
		f[i][1]=f[i-1][2]+1;
		f[i][2]=f[i-2][1]+1;
		if(s[i]!=s[i-1])
			f[i][1]=max(f[i][1],f[i-1][1]+1);
		if(s[i]!=s[i-2]&&s[i-1]!=s[i-3])
			f[i][2]=max(f[i][2],f[i-2][2]+1);
	}
	printf("%d\n",max(f[n][1],f[n][2]));
	return 0;
}