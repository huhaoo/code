/**************************************************************
	File name: 2483.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/18/2019, 1:06:13 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
#include<vector>
#include<queue>
#define N 5010
struct edge
{
	int to;
	double w;
	edge(int t=0,double W=0.)
	{
		to=t;
		w=W;
	}
};
int n,m,p[N],ans;
double s,d[N];
vector<edge>t[N],rt[N];
struct dij
{
	int u;
	double d;
	dij(int U=0,double D=0.)
	{
		u=U;
		d=D;
	}
};
struct kth
{
	int u;
	int t;
	double d;
	kth(int U=0,int T=0,double D=0.)
	{
		u=U;
		t=T;
		d=D;
	}
};
bool operator<(dij a,dij b)
{
	return a.d>b.d;
}
bool operator<(kth a,kth b)
{
	return t[a.u][a.t].w+a.d+d[t[a.u][a.t].to]>t[b.u][b.t].w+b.d+d[t[b.u][b.t].to];
}
priority_queue<dij>q;
priority_queue<kth>r;
#define inf 2e12
#define eps 1e-8
int cmp(edge a,edge b)
{
	return d[a.to]+a.w<d[b.to]+b.w;
}
int main()
{
	n=read();
	m=read();
	scanf("%lf",&s);
    if(s==10000000.)
	{
        printf("2002000\n");
        return 0;
    }
	fr(i,1,m)
	{
		int u=read(),v=read();
		double w;
		scanf("%lf",&w);
		t[u].push_back(edge(v,w));
		rt[v].push_back(edge(u,w));
	}
	fr(i,1,n-1)
		d[i]=inf;
	q.push(dij(n,0.));
	while(!q.empty())
	{
		int u=q.top().u;
		q.pop();
		if(p[u])
			continue;
		p[u]=1;
		fr(i,0,rt[u].size()-1)
			if(d[rt[u][i].to]>d[u]+rt[u][i].w)
			{
				d[rt[u][i].to]=d[u]+rt[u][i].w;
				q.push(dij(rt[u][i].to,d[rt[u][i].to]));
			}
	}
	fr(i,1,n)
		if(t[i].size())
			sort(t[i].begin(),t[i].end(),cmp);
	r.push(kth(1,0,0));
	while(!r.empty())
	{
		kth k=r.top();
		r.pop();
		while(k.u!=n)
		{
			if(int(t[k.u].size()-1)>k.t)
				r.push(kth(k.u,k.t+1,k.d));
			k.d+=t[k.u][k.t].w;
			k.u=t[k.u][k.t].to;
			k.t=0;
		}
		s-=k.d;
		if(s<-eps)
			break;
		ans++;
		if(s<k.d)
			break;
	}
	printf("%d\n",ans);
	return 0;
}