#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
int read()
{
	int c=getchar(),r=0,t=1;
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
#include<vector>
#include<queue>
namespace run
{
	const int N=300010,inf=(1<<30)-1;
	struct city
	{
		int x,y,id;
		city(int _x=0,int _y=0,int _id=0)
		{
			x=_x;
			y=_y;
			id=_id;
		}
	}c[N],kd[N];
	int n,m,cnt,s[N][2],l[N],r[N],d[N],u[N],t[N],w,h,dis[N],vis[N];
	vector<int>jump[N];
	int cmp1(city a,city b)
	{
		return a.x<b.x;
	}
	int cmp2(city a,city b)
	{
		return a.y<b.y;
	}
	int build(int l,int r,int opt)
	{
		if(l>r)
			return 0;
		int k=++cnt;
		if(l==r)
		{
			kd[k]=c[l];
			return k;
		}
		int mid=(l+r)>>1;
		if(opt==0)
			nth_element(c+l,c+mid,c+r+1,cmp1);
		else
			nth_element(c+l,c+mid,c+r+1,cmp2);
		kd[k]=c[mid];
		s[k][0]=build(l,mid-1,opt^1);
		s[k][1]=build(mid+1,r,opt^1);
		return k;
	}
	struct dij
	{
		int k,d;
		dij(int _k=0,int _d=0)
		{
			k=_k;
			d=_d;
		}
	};
	int operator<(dij a,dij b)
	{
		return a.d>b.d;
	}
	priority_queue<dij>q;
	void query(int k,int _l,int _r,int _d,int _u,int l,int r,int d,int u,int __w,int opt)
	{
		if(_l>=l&&_r<=r&&_d>=d&&_u<=u)
		{
			if(!vis[k+n]&&__w<dis[k+n])
			{
				dis[k+n]=__w;
				q.push(dij(-k,__w));
			}
			return;
		}
		if(!vis[kd[k].id]&&dis[kd[k].id]>__w&&kd[k].x>=l&&kd[k].x<=r&&kd[k].y>=d&&kd[k].y<=u)
		{
			dis[kd[k].id]=__w;
			q.push(dij(kd[k].id,__w));
		}
		if(opt==0)
		{
			if(kd[k].x>=l&&s[k][0])
				query(s[k][0],_l,kd[k].x,_d,_u,l,r,d,u,__w,opt^1);
			if(kd[k].x<=r&&s[k][1])
				query(s[k][1],kd[k].x,_r,_d,_u,l,r,d,u,__w,opt^1);
		}
		else
		{
			if(kd[k].y>=d&&s[k][0])
				query(s[k][0],_l,_r,_d,kd[k].y,l,r,d,u,__w,opt^1);
			if(kd[k].y<=u&&s[k][1])
				query(s[k][1],_l,_r,kd[k].y,_u,l,r,d,u,__w,opt^1);
		}
	}
	int main()
	{
		n=read();
		m=read();
		w=read();
		h=read();
		fr(i,1,n)
		{
			c[i].x=read();
			c[i].y=read();
			c[i].id=i;
		}
		build(2,n,0);
		fr(i,1,m)
		{
			jump[read()].push_back(i);
			t[i]=read();
			l[i]=read();
			r[i]=read();
			d[i]=read();
			u[i]=read();
		}
		fr(i,2,n+n)
			dis[i]=inf;
		q.push(dij(1,0));
		while(!q.empty())
		{
			int _u=q.top().k,_d=q.top().d;
			q.pop();
//			printf("%d %d\n",_u,_d);
			if(_u<0)
			{
				if(vis[-_u+n])
					continue;
				vis[-_u+n]=1;
				if(!vis[kd[-_u].id]&&_d<dis[kd[-_u].id])
				{
					dis[kd[-_u].id]=_d;
					q.push(dij(kd[-_u].id,_d));
				}
				if(s[-_u][0]&&!vis[s[-_u][0]+n]&&_d<dis[s[-_u][0]+n])
				{
					dis[s[-_u][0]+n]=_d;
					q.push(dij(-s[-_u][0],_d));
				}
				if(s[-_u][1]&&!vis[s[-_u][1]+n]&&_d<dis[s[-_u][1]+n])
				{
					dis[s[-_u][1]+n]=_d;
					q.push(dij(-s[-_u][1],_d));
				}
			}
			else
			{
				if(vis[_u])
					continue;
				vis[_u]=1;
				fr(i,0,jump[_u].size()-1)
				{
					int j=jump[_u][i];
					query(1,1,w,1,h,l[j],r[j],d[j],u[j],_d+t[j],0);
				}
			}
		}
		fr(i,2,n)
			printf("%d\n",dis[i]);
		return 0;
	}
}
int main()
{
	return run::main();
}