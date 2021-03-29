/**************************************************************
	File name: 2053.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/2/2018, 3:41:32 PM
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
namespace mcmf
{
	const int M=200,N=1000,E=200000,inf=(1<<29);
	int e,u[E],v[E],w[E],c[E],next[E],begin[E],pre[E],ti[N][M],n,m,ans,s,t,dis[N],vis[N];
	queue<int>q;
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
	int spfa()
	{
		fr(i,s,t)vis[i]=0,dis[i]=inf;
		while(!q.empty())q.pop();
		q.push(s);
		dis[s]=0;
		vis[s]=1;
		while(!q.empty())
		{
			int uu=q.front();q.pop();
			// printf("%d\n",uu);
			vis[uu]=0;
			fo(i,uu)
				if(w[i]&&dis[uu]+c[i]<dis[v[i]])
				{
					dis[v[i]]=dis[uu]+c[i];
					pre[v[i]]=i;
					if(!vis[v[i]])
					{
						vis[v[i]]=1;
						q.push(v[i]);
					}
				}
		}
		return dis[t]!=inf;
	}
	void calc()
	{
		int k=t;
		while(k!=s)
		{
			int p=pre[k];
			// printf("%d\n",c[p]);
			w[p]--;
			w[p^1]++;
			ans+=c[p];
			k=u[p];
		}
	}
	int main()
	{
		e=1;
		m=read();
		n=read();
		fr(i,1,n)
			fr(j,1,m)
				ti[i][j]=read();
		s=1;
		fr(i,1,n)
		{
			add(s,i+1,1,0);
			add(i+1,s,0,0);
		}
		fr(i,1,n)
			fr(j,1,m)
				fr(k,1,n)
				{
					add(i+1,j*n+k+1,1,ti[i][j]*k);
					add(j*n+k+1,i+1,0,-ti[i][j]*k);
				}
		t=1+n+n*m+1;
		fr(j,1,m)
			fr(k,1,n)
				{
					add(j*n+k+1,t,1,0);
					add(t,j*n+k+1,0,0);
				}
		while(spfa())calc();
		printf("%.2lf",ans*1.0/n);
		return 0;
	}
}
int main(){return mcmf::main();}