/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Wed 13 Jan 2021 08:56:22 AM CST
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
#include<vector>
#define point std::pair<double,double>
#define x first
#define y second
point operator+(point a,point b){ return {a.x+b.x,a.y+b.y}; }
point operator-(point a,point b){ return {a.x-b.x,a.y-b.y}; }
double operator*(point a,point b){ return a.x*b.y-a.y*b.x; }
point operator*(point a,double b){ return {a.x*b,a.y*b}; }
const int N=50; const double eps=1e-6;
int n,m;
point v;
point a[N],b[N];
double l,r;
double dis(point a){ return sqrt(a.x*a.x+a.y*a.y); }
bool in(double a,double l,double r){ if(l>r) std::swap(l,r); return l-eps<a&&a<r+eps; }
double dis(point a,point b,point c){ return (b-a)*(c-a)/dis(b-c); }
double crosst(std::pair<point,point> a,std::pair<point,point> b)
{
//	if(a.second*b.second<eps) return -1;
	b.y=b.y+b.x;
	double d1=dis(a.x,b.x,b.y),d2=dis(a.x+a.y,b.x,b.y);
	if(fabs(d1-d2)<eps) return -1;
//	printf("%.10lf %.10lf\n",d1,d1-d2);
	return d1/(d1-d2);
}
point cross(std::pair<point,point> a,std::pair<point,point> b){ return a.x+a.y*crosst(a,b); }
double calc(std::pair<point,point> *p,int n)
{
	std::sort(p+1,p+n+1,[](std::pair<point,point> a,std::pair<point,point> b){ return atan2(a.y.y,a.y.x)<atan2(b.y.y,b.y.x); });
	static std::pair<point,point> q[N]; int l,r; q[l=r=1]=p[1];
	static point P[N];
	fr(i,2,n)
	{
		if(fabs(p[i].second*q[r].second)<eps)
		{
			if(p[i].second*(p[i].first-q[r].first)>0){ r--; }
			else continue;
		}
		while(l<r&&p[i].y*(P[r-1]-p[i].x)<0) r--;
		while(l<r&&p[i].y*(P[l]-p[i].x)<0) l++;
		q[++r]=p[i]; P[r-1]=cross(q[r-1],q[r]);
	}
	while(l<r&&q[l].y*(P[r-1]-q[l].x)<0) r--;
	P[r]=cross(q[r],q[l]);
	double ans=0;
	fr(i,l+1,r-1) ans=ans+fabs((P[i]-P[l])*(P[i+1]-P[l]))/2;
	return ans;
}
double calc(double d)
{
	static std::pair<point,point> p[N];
	fr(i,1,n) p[i]={a[i-1]+v*d,a[i]-a[i-1]};
	fr(i,1,m) p[i+n]={b[i-1],b[i]-b[i-1]};
	return calc(p,n+m);
}
int main()
{
	n=read(); fr(i,1,n){ a[i].x=read(); a[i].y=read(); }
	v.x+=read(); v.y+=read();
	m=read(); fr(i,1,m){ b[i].x=read(); b[i].y=read(); }
	v.x-=read(); v.y-=read();
	std::reverse(a+1,a+n+1); std::reverse(b+1,b+m+1);
	a[0]=a[n]; b[0]=b[m];
	l=1e18; r=0;
	fr(i,1,n) fr(j,1,m)
	{
		double t=crosst({a[i],v},{b[j],b[j]-b[j-1]}); point p=cross({a[i],v},{b[j],b[j]-b[j-1]});
		if(t>-eps&&in(p.x,b[j].x,b[j-1].x)&&in(p.y,b[j].y,b[j-1].y)){ l=std::min(l,t); r=std::max(r,t); /*printf("%.10lf\n",t);*/ }
	}
//	putchar(10);
	fr(i,1,n) fr(j,1,m)
	{
		double t=crosst({b[j],point()-v},{a[i],a[i]-a[i-1]}); point p=cross({b[j],point()-v},{a[i],a[i]-a[i-1]});
		if(t>-eps&&in(p.x,a[i].x,a[i-1].x)&&in(p.y,a[i].y,a[i-1].y)){ l=std::min(l,t); r=std::max(r,t); /*printf("%.10lf\n",t);*/ }
	}
	fr(i,1,n) fr(j,1,m)
	{
		point p=cross({a[i],a[i]-a[i-1]},{b[j],b[j]-b[j-1]});
		if(in(p.x,a[i].x,a[i-1].x)&&in(p.x,b[j].x,b[j-1].x)&&in(p.y,a[i].y,a[i-1].y)&&in(p.y,b[j].y,b[j-1].y)) l=0;
	}
	l=std::max(l,(double)0);
//	printf("%.10lf %.10lf\n",l,r);
	if(l-eps>r){ printf("never\n"); return 0; }
	while(r-l>eps)
	{
		double p=(r-l)/3,p1=l+p,p2=r-p;
		if(calc(p1)-calc(p2)>-eps) r=p2;
		else l=p1;
	}
	printf("%.10lf\n",l);
	return 0;
}
