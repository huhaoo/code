/**************************************************************
	File name: 4479.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/5/2018, 9:45:08 AM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(unsigned int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(unsigned int i=(a),_end_=(b);i>=_end_;i--)
unsigned int read()
{
	unsigned int r=0,t=1,c=getchar();
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
#include<queue>
namespace run
{
	#define N 400010
	unsigned int n,m,e,s,begin[N],next[N],to[N],w[N],dis[N],vis[N];
	struct node
	{
		unsigned int p,d;
		node(unsigned int pp=0,unsigned int dd=0){p=pp;d=dd;}
	};
	unsigned int operator<(node a,node b){return a.d>b.d;}
	priority_queue<node>q;
	void add(unsigned int u,unsigned int v,unsigned int ww)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=ww;
	}
	#define fo(i,a) for(unsigned int i=begin[a];i;i=next[i])
	int main()
	{
		n=read();m=read();s=read();
		fr(i,1,m)
		{
			unsigned int u=read(),v=read(),w=read();
			add(u,v,w);
		}
		fr(i,1,n)dis[i]=(1u<<31)-1;
		dis[s]=0;q.push(node(s,0));
		while(!q.empty())
		{
			unsigned int u=q.top().p;q.pop();
			if(vis[u])continue;vis[u]=1;int v;
			fo(i,u)if(dis[u]+w[i]<dis[v=to[i]])
			{
				dis[v]=dis[u]+w[i];
				q.push(node(v,dis[v]));
			}
		}
		fr(i,1,n)printf("%u%c",dis[i],i==n?'\n':' ');
		return 0;
	}
}
int main(){return run::main();}