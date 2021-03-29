/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Sun 04 Aug 2019 08:22:16 PM CST
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
const int N=510;
int n,a[N],b[N],r[N],s,k,ans=1;
int cmp(int a,int c)
{
	return b[a]<b[c];
}
void run(int x)
{
	int o=k;
	fr(i,1,n)
	{
		b[i]=a[i]%x;
		r[i]=i;
	}
	sort(r+1,r+n+1,cmp);
	int i=1,j=n;
	while(i<=j)
	{
		int p=min(b[r[i]],x-b[r[j]]);
		b[r[i]]-=p;
		b[r[j]]+=p;
		o-=p;
		if(b[r[i]]==0)
			i++;
		if(b[r[j]]==x)
			j--;
	}
	if(o>=0)
		ans=max(ans,x);
}
int main()
{
	n=read();
	k=read();
	fr(i,1,n)
	{
		a[i]=read();
		s+=a[i];
	}
	fr(i,1,sqrt(s))
		if(s%i==0)
		{
			run(i);
			run(s/i);
		}
	printf("%d\n",ans);
	return 0;
}
