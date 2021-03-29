/***************************************************************
	File name: A.cpp
	Author: huhao
	Create time: Wed 13 Jan 2021 04:03:25 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
const int N=210; const double eps=1e-9;
#define point std::pair<double,double>
#define x first
#define y second
point operator+(point a,point b){ return {a.x+b.x,a.y+b.y}; }
point operator-(point a,point b){ return {a.x-b.x,a.y-b.y}; }
double operator*(point a,point b){ return a.x*b.y-a.y*b.x; }
point operator*(point a,double b){ return {a.x*b,a.y*b}; }
double dis(point a){ return sqrt(a.x*a.x+a.y*a.y); }
bool in(double a,double l,double r){ if(l>r) std::swap(l,r); return l-eps<a&&a<r+eps; }
bool in(point a,point b,point c){ return in(a.x,b.x,c.x)&&in(a.y,b.y,c.y); }
double dis(point a,point b,point c){ return (b-a)*(c-a)/dis(b-c); }
double crosst(std::pair<point,point> a,std::pair<point,point> b)
{
	double d1=dis(a.x,b.x,b.y),d2=dis(a.y,b.x,b.y);
	if(fabs(d1-d2)<eps) return -1;
//	printf("  %.10lf %.10lf\n",d1,d2);
	return d1/(d1-d2);
}
point cross(std::pair<point,point> a,std::pair<point,point> b){ return a.x+(a.y-a.x)*crosst(a,b); }
double ans; int n;
point p[N];
int main()
{
	n=read();
	fr(i,1,n){ p[i].x=read(); p[i].y=read(); }
	p[0]=p[n]; p[n+1]=p[1];
	fr(i,1,n) fr(j,i+1,n)
	{
		double l=-1e18,r=1e18,u;
		fr(k,1,n) if((in(u=crosst({p[k-1],p[k]},{p[i],p[j]}),0,1)))
		{
			double q=crosst({p[i],p[j]},{p[k-1],p[k]}); int op=0,flag=0;
			if(u<eps||u>1-eps)
			{
				if(u<eps)
				{
					if((p[j]-p[i])*(p[k]-p[k-1])<-eps) flag=1;
				}
				else if(u>1-eps)
				{
					if((p[j]-p[i])*(p[k]-p[k-1])>eps) flag=1;
				}
				if(op==1) std::swap(i,j);
				if(flag) continue;
			}
			if(q<eps) l=std::max(l,q);
			else r=std::min(r,q);
		}
		printf("%d %d  %.10lf %.10lf\n",i,j,l,r);
		if(r<1-eps) continue;
		ans=std::max(ans,dis(p[i]-p[j])*(r-l));
	}
	printf("%.10lf\n",ans);
	return 0;
}
