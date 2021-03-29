/***************************************************************
	File name: 线性规划.cpp
	Author: huhao
	Create time: Fri 19 Jun 2020 04:17:01 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
#include<stdlib.h>
const int N=50;
const double eps=1e-6,inf=1e20;
int n,id[N],m,T;
double a[N][N],ans[N];
void pivot(int s,int t)
{
	std::swap(id[s+n],id[t]);
	double k=a[s][t]; a[s][t]=1.;
	fr(i,0,n) a[s][i]/=k;
	fr(i,0,m) if(fabs(a[i][t])>eps&&i!=s)
	{
		double k=a[i][t]; a[i][t]=0;
		fr(j,0,n) a[i][j]-=k*a[s][j];
	}
}
int init()
{
	while(1)
	{
		int s=0,t=0;
		fr(i,1,m) if(a[i][0]<-eps&&(!s||rand()%3==0)) s=i;
		if(!s) return 1;
		fr(i,1,n) if(a[s][i]<-eps&&(!t||rand()%3==0)) t=i;
		if(!t){ printf("Infeasible\n"); return 0; }
		pivot(s,t);
	}
}
int simplex()
{
	while(1)
	{
		int s=0,t=0; double mi=inf;
		fr(i,1,n) if(a[0][i]>eps){ t=i; break; }
		if(!t) return 1;
		fr(i,1,m) if(a[i][t]>eps&&a[i][0]/a[i][t]<mi){ s=i; mi=a[i][0]/a[i][t]; }
		if(!s){ printf("Unbounded\n"); return 0; }
		pivot(s,t);
	}
}
int main()
{
	srand(1000000007);
	n=read(); m=read(); T=read();
	fr(i,1,n) a[0][i]=read()*1.;
	fr(i,1,m)
	{
		fr(j,1,n) a[i][j]=read()*1.;
		a[i][0]=read()*1.;
	}
	fr(i,1,n) id[i]=i;
	if(init()&&simplex())
	{
		printf("%.10lf\n",-a[0][0]);
		fr(i,1,m) ans[id[i+n]]=a[i][0];
		if(T) fr(i,1,n) printf("%.10lf%c",ans[i],i==n?'\n':' ');
	}
	return 0;
}
