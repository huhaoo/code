/***************************************************************
	File name: 3322.cpp
	Author: huhao
	Create time: Fri 27 Sep 2019 08:54:04 AM CST
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
const int N=1000010;
#define i64 long long
int a[N],n;
i64 ans;
void dfs(int k,int c,i64 s)
{
	if(k==n)
	{
		ans=ans+s;
		return;
	}
	for(int i=0;i<(1<<n);i+=(1<<k))
	{
		fr(j,1,(1<<k)-1)
			if(a[i+j]!=a[i+j-1]+1)
				return;
	}
	int v[5],t=0;
	for(int i=0;i<(1<<n);i+=(1<<(k+1)))
		if(a[i+(1<<k)-1]+1!=a[i+(1<<k)])
		{
			v[++t]=i;
			if(t>2)
				return;
		}
	if(!t)
		dfs(k+1,c,s);
#define mv(l,r) fr(i,0,(1<<k)-1)swap(a[l+i],a[r+i]);
	else if(t==1)
	{
		mv(v[1],v[1]+(1<<k));
		dfs(k+1,c+1,s*c);
		mv(v[1],v[1]+(1<<k));
	}
	else if(t==2)
	{
		//00
		mv(v[1],v[2]);
		dfs(k+1,c+1,s*c);
		mv(v[1],v[2]);
		//01
		mv(v[1],v[2]+(1<<k));
		dfs(k+1,c+1,s*c);
		mv(v[1],v[2]+(1<<k));
		//10
		mv(v[1]+(1<<k),v[2]);
		dfs(k+1,c+1,s*c);
		mv(v[1]+(1<<k),v[2]);
		//11
		mv(v[1]+(1<<k),v[2]+(1<<k));
		dfs(k+1,c+1,s*c);
		mv(v[1]+(1<<k),v[2]+(1<<k));
	}
}
int main()
{
	n=read();
	fr(i,0,(1<<n)-1)
		a[i]=read()-1;
	dfs(0,1,1);
	printf("%lld\n",ans);
	return 0;
}
