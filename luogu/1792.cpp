/***************************************************************
	File name: 1792.cpp
	Author: huhao
	Create time: Sun 29 Sep 2019 06:29:30 PM CST
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
#include<queue>
const int N=200010;
int a[N],l[N],r[N],n,m,ans,vis[N];
priority_queue<pair<int,int> > q;
int main()
{
	n=read();
	m=read();
	if(n<m*2)
	{
		printf("Error!\n");
		return 0;
	}
	fr(i,1,n)
	{
		a[i]=read();
		q.push(make_pair(a[i],i));
	}
	fr(i,1,n-1)
	{
		l[i+1]=i;
		r[i]=i+1;
	}
	l[1]=n;
	r[n]=1;
	while(m--)
	{
		int p=q.top().second;
		while(vis[p])
		{
			q.pop();
			p=q.top().second;
		}
		q.pop();
		ans+=a[p];
		while(vis[l[p]])
			l[p]=l[l[p]];
		while(vis[r[p]])
			r[p]=r[r[p]];
		a[p]=a[l[p]]+a[r[p]]-a[p];
		vis[l[p]]=vis[r[p]]=1;
		q.push(make_pair(a[p],p));
	}
	printf("%d\n",ans);
	return 0;
}
