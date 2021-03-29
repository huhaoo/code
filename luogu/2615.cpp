/**************************************************************
	File name: 2615.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/1/2018, 1:55:31 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
#define N 110
int n,a[N][N],x,y;
int main()
{
	n=read();x=1;y=n/2+1;
	fr(i,1,n*n)
	{
		a[x][y]=i;
		x--;y++;
		if(x==0&&y==n+1){x+=2;y--;}
		if(x==0)x=n;if(y==n+1)y=1;
		if(a[x][y]){x+=2;y--;}
	}
	fr(i,1,n)fr(j,1,n)printf("%d%c",a[i][j],j==n?'\n':' ');
	return 0;
}