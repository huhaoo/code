/**************************************************************
	File name: 4232.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/10/2018, 7:58:35 PM
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
#include<stdlib.h>
namespace run
{
	#define N 1010
	#define NN 30
	int nn,T,begin[N],next[N],to[N],e,n,m;
	double a[N][N],f[NN][NN][NN];
	#define fo(i,a) for(int i=begin[a];i;i=next[i])
	#define eps 1e-8
	void add(int u,int v)
	{
		e++;
		to[e]=v;
		next[e]=begin[u];
		begin[u]=e;
	}
	void init(int nn,int mm)
	{
		n=nn;
		m=mm;
		fr(i,0,m)
			fr(j,0,n)
				a[i][j]=0.;
	}
	void pivot(int l,int e)//l:[1..m],e:[1..n]
	{
		double k=a[l][e];a[l][e]=1.;
		fr(i,0,n)a[l][i]/=k;
		fr(i,0,m)
			if(i!=l&&fabs(a[i][e])>eps)
			{
				k=a[i][e];a[i][e]=0;
				fr(j,0,n)
					a[i][j]-=a[l][j]*k;
			}
	}
	int init()
	{
		while(1)
		{
			int l=0,e=0;
			fr(i,1,m)
				if(a[i][0]<-eps&&(!l||(rand()&1)))
					l=i;
			if(!l)break;
			fr(i,1,n)
				if(a[l][i]<-eps&&(!e||(rand()&1)))
					e=i;
			if(!e)return 0;
			pivot(l,e);
		}
		return 1;
	}
	int simplex()
	{
		while(1)
		{
			int l=0,e=0;
			double mi=1e15;
			fr(i,1,n)
				if(a[0][i]>eps)
				{
					e=i;
					break;
				}
			if(!e)break;
			fr(i,1,m)
				if(a[i][e]>eps&&a[i][0]/a[i][e]<mi)
				{
					mi=a[i][0]/a[i][e];
					l=i;
				}
			if(!l)return 0;
			pivot(l,e);
		}
		return 1;
	}
	double dfs(int x,int y,int t)
	{
		if(x==y||t>T)return 1.*t;
		if(f[x][y][t])return f[x][y][t];
		int dx=0,dy=0;
		fo(i,x)fo(j,y)dfs(to[i],to[j],t+1);
		fo(i,x)dx++;
		fo(i,y)dy++;
		//dx->n,dy->m
		init(dy,dx);
		fr(i,1,n)a[0][i]=1.;
		dx=0;dy=0;
		fo(i,x)
		{
			dx++;
			dy=0;
			fo(j,y)
			{
				dy++;
				a[dx][dy]=dfs(to[i],to[j],t+1);
			}
			a[dx][0]=1;
		}
		if(init()&&simplex())f[x][y][t]=-1./a[0][0];
		return f[x][y][t];
	}
	int main()
	{
		srand((unsigned long long)new char);
		nn=read();int m=read(),x=read(),y=read();T=read();
		fr(i,1,nn)add(i,i);
		while(m--)
		{
			int u=read(),v=read();
			add(u,v);
		}
		printf("%.3lf\n",dfs(x,y,0));
		return 0;
	}
}
int main(){return run::main();}