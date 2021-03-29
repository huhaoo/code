/***************************************************************
	File name: 1256F.cpp
	Author: huhao
	Create time: Mon 04 Nov 2019 09:55:24 PM CST
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
int q,n,a[N];
char s[N],t[N];
int main()
{
	q=read();
	while(q--)
	{
		int flag=0;
		n=read();
		scanf("%s%s",s+1,t+1);
		fr(i,0,25)
			a[i]=0;
		fr(i,1,n)
		{
			a[s[i]-'a']++;
			if(a[s[i]-'a']>=2)
				flag=1;
		}
		fr(i,1,n)
			a[t[i]-'a']--;
		fr(i,0,25)
			if(a[i])
				flag=-1;
		if(flag==-1)
		{
			printf("NO\n");
			continue;
		}
		if(flag==1)
		{
			printf("YES\n");
			continue;
		}
		int ans=0;
		fr(i,0,25)
			a[i]=0;
		fr(i,1,n)
		{
			fr(j,s[i]-'a'+1,25)
				ans^=a[j];
			a[s[i]-'a']^=1;
		}
		fr(i,0,25)
			a[i]=0;
		fr(i,1,n)
		{
			fr(j,t[i]-'a'+1,25)
				ans^=a[j];
			a[t[i]-'a']^=1;
		}
		printf("%s\n",ans?"NO":"YES");
	}
	return 0;
}
