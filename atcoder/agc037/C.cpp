/**************************************************************
	File name: C.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/8/17 下午8:51:35
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
const int N=200010;
int a[N],b[N];
#include<queue>
priority_queue<pair<int,int>>q;
int n;
long long ans;
int main()
{
	n=read();
	fr(i,1,n)
		a[i]=read();
	fr(i,1,n)
	{
		b[i]=read();
		if(b[i]>a[i])
			q.push(make_pair(b[i],i));
		if(b[i]<a[i])
		{
			printf("-1\n");
			return 0;
		}
	}
	b[0]=b[n];
	b[n+1]=b[1];
	while(!q.empty())
	{
		int p=q.top().second;
		q.pop();
		int k=max(b[p]-max(a[p],max(b[p-1],b[p+1]))-1,0)/(b[p-1]+b[p+1])+1;
		ans+=k;
		b[p]-=k*(b[p-1]+b[p+1]);
		b[0]=b[n];
		b[n+1]=b[1];
		if(b[p]<a[p])
		{
			printf("-1\n");
			return 0;
		}
		if(b[p]!=a[p])
			q.push(make_pair(b[p],p));
	}
	printf("%lld\n",ans);
	return 0;
}