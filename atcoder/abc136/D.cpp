/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Sun 04 Aug 2019 08:09:15 PM CST
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
const int N=100010;
char s[N];
int n,t[N],ans[N];
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	fr(i,1,n)
		if(s[i]=='L')
		{
			t[i]=t[i-1];
		}
		else
		{
			int j=i;
			while(s[j]=='R')
				j++;
			j--;
			fr(k,i,j)
				t[k]=j;
			i=j;
		}
	fr(i,1,n)
		if(abs(i-t[i])%2==0)
			ans[t[i]]++;
		else
			ans[t[i]+1]++;
	fr(i,1,n)
		printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}
