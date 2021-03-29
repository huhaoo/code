/***************************************************************
	File name: 1214C.cpp
	Author: huhao
	Create time: Wed 04 Sep 2019 05:16:18 PM CST
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
const int N=2000010;
int s,n;
char c[N];
int main()
{
	n=read();
	scanf("%s",c+1);
	fd(i,n,1)
		if(c[i]=='(')
		{
			c[i]=0;
			c[0]='(';
			break;
		}
	fr(i,0,n)
	{
		if(c[i]=='(')
			s++;
		else if(c[i]==')')
			s--;
		if(s<0)
		{
			printf("No\n");
			return 0;
		}
	}
	printf(s==0?"Yes\n":"No\n");
	return 0;
}
