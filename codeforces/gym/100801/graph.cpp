/***************************************************************
	File name: graph.cpp
	Author: huhao
	Create time: Wed 04 Nov 2020 09:43:17 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
#include<vector>
std::priority_queue<int> q;
std::priority_queue<int,std::vector<int>,std::greater<int> > Q;
const int N=100010;
std::vector<int> e[N];
int n,d[N],k,m,u[N],v[N],a[N];
int main()
{
	freopen("graph.in","r",stdin); freopen("graph.out","w",stdout);
	n=read(); m=read(); k=read();
	fr(i,1,m){ int u=read(),v=read(); e[u].push_back(v); d[v]++; }
	fr(i,1,n) if(!d[i]) Q.push(i);
	m=0;
	fr(t,1,n)
	{
		while(k&&Q.size()>1){ k--; q.push(Q.top()); Q.pop(); }
		if(k&&!q.empty()&&!Q.empty()&&q.top()>Q.top()){ k--; q.push(Q.top()); Q.pop(); }
		if(Q.empty()){ m++; a[t]=v[m]=q.top(); q.pop(); u[m]=a[t-1]; }
		else{ a[t]=Q.top(); Q.pop(); }
		for(auto i:e[a[t]]){ d[i]--; if(!d[i]) Q.push(i); }
	}
	fr(i,1,n) printf("%d%c",a[i],i==n?'\n':' ');
	printf("%d\n",m);
	fr(i,1,m) printf("%d %d\n",u[i],v[i]);
	return 0;
}
