/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Sun 08 Nov 2020 03:14:24 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
const int N=410,DEBUG=0;
namespace simplex
{
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
	double solve(int _n,int _m,double A[N][N])
	{
		if(DEBUG) printf("%d %d\n",_n,_m);
		if(DEBUG) fr(i,0,_m) fr(j,0,_n) printf("%.10lf%c",A[i][j],j==end_j?'\n':' ');
		n=_n; m=_m; fr(i,0,m) fr(j,0,n) a[i][j]=A[i][j];
		assert(init()&&simplex()); if(DEBUG) printf("%.10lf\n",-a[0][0]);
		return -a[0][0];
	}
}
int n,m,id[N][N],d[N][N],D[N][N],_d[N];
double a[N][N],A[N][N],v[N][N]; int _n,_m;
void Add(double *b,int id,double t){ fr(i,0,_n) b[i]+=t*v[id][i]; }
int main()
{
	srand((unsigned long long)new char);
	n=read();
	fr(i,1,n) fr(j,1,n){ d[i][j]=D[i][j]=read(); if(d[i][j]>0) _d[id[i][j]=++m]=d[i][j]; }
	fr(i,1,n) fr(j,1,n) if(d[i][j]==-1) d[i][j]=1<<20;
	fr(k,1,n) fr(i,1,n) fr(j,1,n) d[i][j]=std::min(d[i][j],d[i][k]+d[k][j]);
//	fr(i,1,n) fr(j,1,n) printf("%d%c",d[i][j],j==n?'\n':' ');
	_n=m;
	fr(i,1,m) v[i][i]=1;
	fr(_,1,read())
	{
		int u=read()+1,v=read()+1;
		static double b[N];
		fr(i,0,_n) b[i]=0;
		b[0]=-read();
		while(u!=v){ fr(j,1,n) if(j!=u&&D[u][j]>0&&D[u][j]+d[j][v]==d[u][v]){ Add(b,id[u][j],1); u=j; break; } }
		int p=1,P=0;
		while(p<=_n&&fabs(b[p])<1e-8) p++;
		if(p>_n){ assert(fabs(b[0])<1e-8); continue; }
		fr(i,0,_n) if(i!=p) b[i]/=b[p];
		b[p]=1;
		fr(i,1,m)
		{
			int flag=1;
			fr(j,0,_n) if(fabs(::v[i][j]-(j==p?1:0))>1e-8) flag=0;
			if(flag) P=i;
		}
		assert(P);
/*		fr(i,0,_n) printf("%.10lf%c",b[i],i==_n?'\n':' ');
		putchar(10);
		fr(i,1,m) fr(j,0,_n) printf("%.10lf%c",::v[i][j],j==_n?'\n':' ');
		printf("%d\n",p);
		printf("%d\n",P);
		putchar(10);*/
		fr(i,0,_n) ::v[P][i]=-b[i];
		_n--;
		std::swap(::v[P][p],::v[P][_n+1]);
		fr(i,1,m) if(i!=P){ std::swap(::v[i][p],::v[i][_n+1]); Add(::v[i],P,::v[i][_n+1]); }
	}
//	fr(i,1,m) fr(j,0,_n) printf("%.10lf%c",v[i][j],j==_n?'\n':' ');
	fr(i,1,m)
	{
		_m++; Add(a[_m],i,1); a[_m][0]=2*_d[i]-a[_m][0];
		_m++; Add(a[_m],i,-1); a[_m][0]=-_d[i]-a[_m][0];
	}
	fr(_,1,read())
	{
		int u=read()+1,v=read()+1,U=u,V=v; double ans;
//		if(u==v){ printf("%d %d 0 0\n",u-1,v-1); continue; }
		if(!DEBUG) printf("%d %d ",u-1,v-1);
		u=U; v=V;
		fr(i,0,_m) fr(j,0,_n) A[i][j]=a[i][j];
		while(u!=v){ fr(j,1,n) if(j!=u&&D[u][j]>0&&D[u][j]+d[j][v]==d[u][v]){ Add(A[0],id[u][j],-1); u=j; break; } }
		ans=A[0][0]; A[0][0]=0;
		if(DEBUG) simplex::solve(_n,_m,A);
		if(!DEBUG) printf("%.10lf ",-(ans+simplex::solve(_n,_m,A)));
		u=U; v=V;
		fr(i,0,_m) fr(j,0,_n) A[i][j]=a[i][j];
		while(u!=v){ fr(j,1,n) if(j!=u&&D[u][j]>0&&D[u][j]+d[j][v]==d[u][v]){ Add(A[0],id[u][j],1); u=j; break; } }
		ans=A[0][0]; A[0][0]=0;
		if(DEBUG) simplex::solve(_n,_m,A);
		if(!DEBUG) printf("%.10lf\n",ans+simplex::solve(_n,_m,A));
	}
	return 0;
}
