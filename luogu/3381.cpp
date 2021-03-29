/**************************************************************
	File name: 3381.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 6/30/2018, 1:54:14 PM
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
#include<queue>
namespace ek
{
	#define N 5010
	#define M 100010
	#define inf (1<<29)
	int u[M],v[M],begin[N],next[M],w[M],c[M],e,n,m,s,t,pre[N],aw,ac,a[N],dis[N];
	void add(int uu,int vv,int ww,int cc)
	{
		e++;
		u[e]=uu;
		v[e]=vv;
		w[e]=ww;
		c[e]=cc;
		next[e]=begin[uu];
		begin[uu]=e;
	}
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	queue<int>q;
	int bfs()
	{
		fr(i,1,n)a[i]=0,dis[i]=inf;
		while(!q.empty())q.pop();
		q.push(s);
		a[s]=1;
		dis[s]=0;
		while(!q.empty())
		{
			int uu=q.front();
			q.pop();
			a[uu]=0;
			fo(i,uu)
				if(w[i]&&dis[uu]+c[i]<dis[v[i]])
				{
					if(!a[v[i]])
					{
						a[v[i]]=1;
						q.push(v[i]);
					}
					pre[v[i]]=i;
					dis[v[i]]=dis[uu]+c[i];
				}
		}
		return dis[t]!=inf;
	}
	void run()
	{
		int f=inf,k=t;
		while(k!=s)
		{
			f=min(f,w[pre[k]]);
			k=u[pre[k]];
		}
		aw+=f;
		k=t;
		while(k!=s)
		{
			ac+=f*c[pre[k]];
			w[pre[k]]-=f;
			w[pre[k]^1]+=f;
			k=u[pre[k]];
		}
	}
	int main()
	{
		e=1;
		n=read();
		m=read();
		s=read();
		t=read();
		fr(i,1,m)
		{
			int uu=read(),vv=read(),ww=read(),cc=read();
			add(uu,vv,ww,cc);
			add(vv,uu,0,-cc);
		}
		while(bfs())run();
		printf("%d %d\n",aw,ac);
		return 0;
	}
}
int main(){return ek::main();}