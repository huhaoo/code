/**************************************************************
	File name: 4142.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 6/30/2018, 3:56:22 PM
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
namespace EK
{
	#define N 600
	#define NN 25100
	#define M 50100
	int u[NN],v[NN],w[M],ap[N][N],begin[NN],next[NN],c[NN],ans,pre[NN],vis[NN],n,m,k,e,num[N][N],top,s,t,dis[NN];
	int mx[4]={0,0,1,-1};
	int my[4]={1,-1,0,0};
	void add(int uu,int vv,int ww,int cc)
	{
//		printf("%d %d %d %d\n",uu,vv,ww,cc);
		e++;
		u[e]=uu;
		v[e]=vv;
		w[e]=ww;
		c[e]=cc;
		next[e]=begin[uu];
		begin[uu]=e;
	}
	#define inf (1<<29)
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	queue<int>q;
	int spfa()
	{
		fr(i,s,t)dis[i]=inf;
		fr(i,s,t)vis[i]=0;
		dis[s]=0;
		vis[s]=1;
		q.push(s);
		while(!q.empty())
		{
			int uu=q.front();
//			printf("%d\n",uu);
			q.pop();
			vis[uu]=0;
			fo(i,uu)
				if(w[i]&&dis[uu]+c[i]<dis[v[i]])
				{
					dis[v[i]]=dis[uu]+c[i];
					pre[v[i]]=i;
					if(!vis[v[i]])
					{
						q.push(v[i]);
						vis[v[i]]=1;
					}
				}
		}
		return dis[t]!=inf;
	}
	int run()
	{
//		return 0;
		int r=0,k=t;
		while(k!=s)
		{
//			printf("%d %d %d %d\n",k,pre[k],w[pre[k]],c[pre[k]]);
			r+=c[pre[k]];
			w[pre[k]]--;
			w[pre[k]^1]++;
			k=u[pre[k]];
		}
		return r;
	}
	int main()
	{
		e=1;
		n=read();
		m=read();
		k=read();
		fr(i,1,n)fr(j,1,n)ans+=(ap[i][j]=read());
		fr(i,1,k)
		{
			int x=read(),y=read();
			ap[x][y]=-1;
		}
		s=++top;
		fr(i,1,n)
			fr(j,1,n)
				if(ap[i][j]!=-1&&(i+j)%2==0&&i%2==1)
					num[i][j]=++top;
		fr(i,1,n)
			fr(j,1,n)
				if(ap[i][j]!=-1&&(i+j)%2==0&&i%2==0)
					num[i][j]=++top;
		fr(i,1,n)
			fr(j,1,n)
				if(ap[i][j]!=-1&&(i+j)%2==1)
				{
					num[i][j]=++top;
					top++;
					add(num[i][j],num[i][j]+1,1,-ap[i][j]);
					add(num[i][j]+1,num[i][j],0,ap[i][j]);
				}
		t=++top;
		fr(i,1,n)
			fr(j,1,n)
				if(ap[i][j]!=-1&&(i+j)%2==0&&i%2==1)
				{
					add(s,num[i][j],1,0);
					add(num[i][j],s,0,0);
				}
		fr(i,1,n)
			fr(j,1,n)
				if(ap[i][j]!=-1&&(i+j)%2==0&&i%2==0)
				{
					add(num[i][j],t,1,0);
					add(t,num[i][j],0,0);
				}
		fr(i,1,n)
			fr(j,1,n)
				if(ap[i][j]!=-1&&(i+j)%2==1)
					fr(k,0,3)
					{
						int x=i+mx[k],y=j+my[k];
						if(x<1||y<1||x>n||y>n||ap[x][y]==-1)continue;
						if(x&1)
						{
							add(num[x][y],num[i][j],1,0);
							add(num[i][j],num[x][y],0,0);
						}
						else
						{
							add(num[i][j]+1,num[x][y],1,0);
							add(num[x][y],num[i][j]+1,0,0);
						}
					}
		fr(i,1,m)
		{
			if(!spfa())break;
			int c=run();
			if(c>=0)break;
			ans+=c;
		}
/*		fr(i,1,n)
			fr(j,1,n)
				printf("%d%c",num[i][j],j==n?'\n':' ');*/
		printf("%d\n",ans);
		return 0;
	}
}
int main(){return EK::main();}