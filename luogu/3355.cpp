/**************************************************************
	File name: 3355.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/2/2018, 5:10:30 PM
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
namespace dinic
{
	#define N 2100
	#define NN 400010
	#define E 10000010
	int mx[8]={2,2,1,1,-1,-1,-2,-2},my[8]={1,-1,2,-2,2,-2,1,-1};
	int s,t,num[N][N],ap[N][N],begin[NN],next[E],w[E],to[E],e,n,m,top,ans,dis[NN],l,r,q[NN],cur[NN];
	void add(int u,int v,int ww)
	{
//		printf("%d %d %d\n",u,v,ww);
		e++;
		next[e]=begin[u];
		begin[u]=e;
		to[e]=v;
		w[e]=ww;
	}
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	int check(int x,int y)
	{
		return x>=1&&y>=1&&x<=n&&y<=n&&(!ap[x][y]);
	}
	int bfs()
	{
		fr(i,s,t)dis[i]=0;
		fr(i,s,t)cur[i]=begin[i];
		dis[t]=1;
		q[l=r=1]=t;
		while(l<=r)
		{
			int u=q[l];
			l++;
			fo(i,u)
				if(w[i^1])
				{
					int v=to[i];
					if(dis[v])continue;
					dis[v]=dis[u]+1;
					if(v==s)return 1;
					q[++r]=v;
				}
		}
		return 0;
	}
	int dinic(int u,int f)
	{
//		printf("%d %d %d\n",u,f,t);
		int r=0;
		if(u==t)return f;
		for(int i=cur[u];i;i=next[i],cur[u]=i)
			if(w[i])
			{
				int v=to[i];
				if(dis[v]!=dis[u]-1)continue;
				int ff=dinic(v,min(w[i],f));
//				printf("%d %d %d %d %d\n",u,v,f,ff,w[i]);
				if(!ff)continue;
				if(!f)break;
				f-=ff;
				r+=ff;
				w[i]-=ff;
				w[i^1]+=ff;
			}
		return r;
	}
	#define inf (1<<29)
	int main()
	{
		e=1;
		n=read();
		m=read();
		fr(i,1,m)
		{
			int x=read(),y=read();
			ap[x][y]=1;
		}
		s=++top;
		fr(i,1,n)
			fr(j,1,n)
				if(!ap[i][j]&&(i+j)%2==0)
					num[i][j]=++top;
		fr(i,1,n)
			fr(j,1,n)
				if(!ap[i][j]&&(i+j)%2==1)
					num[i][j]=++top;
		t=++top;
		fr(i,1,n)
			fr(j,1,n)
				if(!ap[i][j])
				{
					if((i+j)%2==0)
					{
						add(s,num[i][j],1);
						add(num[i][j],s,0);
					}
					else
					{
						add(num[i][j],t,1);
						add(t,num[i][j],0);
					}
				}
		fr(i,1,n)
			fr(j,1,n)
				if(!ap[i][j]&&(i+j)%2==0)
					fr(k,0,7)
					{
						int x=i+mx[k],y=j+my[k];
						if(!check(x,y))continue;
						add(num[i][j],num[x][y],1);
						add(num[x][y],num[i][j],0);
//						printf("%d %d %d %d %d\n",i,j,x,y,k);
					}
		while(bfs())
			ans+=dinic(s,inf);
			//{ans+=dinic(s,inf);fr(i,s,t)printf("%d%c",dis[i],i==t?'\n':' ');return 0;}
		printf("%d\n",n*n-m-ans);
		return 0;
	}
}
int main(){return dinic::main();}