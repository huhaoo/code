/****************************************************************
	File name: 3953.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/31/2018, 8:34:44 AM
****************************************************************/
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
namespace run
{
	#define N 400010
	#define K 60
	int n,m,nn,mm,u[N],v[N],p[N],w[N],begin[N],next[N],to[N],ww[N],e,k,mod,vis[N],dis1[N],disn[N],d[N],cnt,r[N];
	int f[N][K],ans;
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	void add(int u,int v,int w)
	{
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		ww[e]=w;
	}
	struct visit
	{
		int pos,d;
		visit(int p=0,int dd=0){pos=p;d=dd;}
	};
	bool operator<(visit a,visit b){return a.d>b.d;}
	priority_queue<visit>q;
	queue<int>qq;
	int main()
	{
		n=read();m=read();k=read();mod=read();
		fr(i,1,n)begin[i]=0;e=0;
		fr(i,1,m)
		{
			u[i]=read();v[i]=read();w[i]=read();
			add(u[i],v[i],w[i]);
		}
		fr(i,1,n)dis1[i]=(1<<29);
		dis1[1]=0;q.push(visit(1,0));
		fr(i,1,n)vis[i]=0;
		while(!q.empty())
		{
			int u=q.top().pos,v;q.pop();
			if(vis[u])continue;
			vis[u]=1;
			fo(i,u)
				if(dis1[u]+w[i]<dis1[v=to[i]])
				{
					dis1[v]=dis1[u]+w[i];
					q.push(visit(v,dis1[v]));
				}
		}
		fr(i,1,n)begin[i]=0;e=0;
		fr(i,1,m)add(v[i],u[i],w[i]);
		fr(i,1,n)disn[i]=(1<<29);
		disn[n]=0;q.push(visit(n,0));
		fr(i,1,n)vis[i]=0;
		while(!q.empty())
		{
			int u=q.top().pos,v;q.pop();
			if(vis[u])continue;
			vis[u]=1;
			fo(i,u)
				if(disn[u]+w[i]<disn[v=to[i]])
				{
					disn[v]=disn[u]+w[i];
					q.push(visit(v,disn[v]));
				}
		}
		fr(i,1,n)p[i]=0;nn=0;mm=0;
		fr(i,1,n)if(dis1[i]+disn[i]<=dis1[n]+k)p[i]=++nn;
		fr(i,1,m)if(p[u[i]]&&p[v[i]])
		{mm++;w[mm]=disn[v[i]]+w[i]-disn[u[i]];u[mm]=p[u[i]];v[mm]=p[v[i]];}
		fr(i,1,n)begin[i]=0;
		n=nn;m=mm;e=0;
		fr(i,1,n)d[i]=0;
		fr(i,1,m)if(!w[i]){add(v[i],u[i],0);d[u[i]]++;}
		fr(i,1,n)if(!d[i])qq.push(i);cnt=0;
		while(!qq.empty())
		{
			int u=qq.front(),v;qq.pop();
			r[++cnt]=u;
			fo(i,u)
			{
				d[v=to[i]]--;
				if(!d[v])qq.push(v);
			}
		}
		if(cnt!=n){printf("-1\n");return 0;}
		fr(i,1,n)begin[i]=0;e=0;
		fr(i,1,m)add(v[i],u[i],w[i]);
		fr(i,1,n)fr(j,0,k)f[i][j]=0;
		f[1][0]=1;
		fr(i,0,k)fd(j,n,1)fo(o,r[j])if(i-w[o]>=0)f[r[j]][i]=(f[r[j]][i]+f[to[o]][i-w[o]])%mod;
		ans=0;
		fr(i,0,k)ans=(ans+f[n][i])%mod;
		printf("%d\n",ans);
		return 0;
	}
}
int main()
{
	fr(i,1,read())run::main();
	return 0;
}