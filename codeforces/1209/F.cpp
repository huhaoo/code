/**************************************************************
	File name: 1209F.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/9/14 下午11:02:44
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
#define int long long
const int N=100010,inf=1ll<<40;
int n,m,d[N],l[N],L[N],D[N],vis[N];
#include<vector>
vector<pair<int,int> > e[N];
#include<queue>
priority_queue<pair<int,int> >q;
signed main()
{
	n=read();
	m=read();
	L[0]=1;
	fr(i,1,m)
	{
		l[i]=l[i/10]+1;
		L[i]=L[i/10]*10;
	}
	fr(i,1,m)
	{
		int u=read(),v=read();
		e[u].push_back(make_pair(v,i));
		e[v].push_back(make_pair(u,i));
	}
	fr(i,2,n)
		d[i]=inf;
	q.push(make_pair(0,1));
	while(!q.empty())
	{
		int u=q.top().second;
		q.pop();
		if(vis[u])
			continue;
		vis[u]=1;
		for(auto v:e[u])
			if(!vis[v.first]&&d[v.first]>d[u]+l[v.second])
			{
				d[v.first]
			}
	}
	return 0;
}