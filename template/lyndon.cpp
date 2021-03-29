/***************************************************************
	File name: 129.cpp
	Author: huhao
	Create time: Thu 05 Sep 2019 01:46:30 PM CST
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
const int N=(1<<20)+10;
char s[N];
int n,m,a[N];
int duval(char *s,int n,int *a)
{
	int i=1,j,k,m=0;
	while(i<=n)
	{
		j=i;
		k=i+1;
		while(k<=n)
		{
			if(s[k]==s[j])
			{
				k++;
				j++;
			}
			else if(s[k]>s[j])
			{
				k++;
				j=i;
			}
			else
				break;
		}
		int l=k-j;
		while(i+l<=k)
		{
			i+=l;
			a[++m]=i-1;
		}
	}
	return m;
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	m=duval(s,n,a);
	fr(i,1,m)
		printf("%d%c",a[i],i==m?'\n':' ');
	return 0;
}
