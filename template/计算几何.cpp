/***************************************************************
	File name: 计算几何.cpp
	Author: huhao
	Create time: Tue 08 Sep 2020 08:24:54 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<functional>
#define int int32_t
#define i64 int64_t
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
struct point // point or vec
{
	double x,y;
	point(double X=0,double Y=0){ x=X; y=Y; }
};
const double pi=acos(-1.);
inline point operator+(point a,point b){ return point(a.x+b.x,a.y+b.y); }
inline point operator-(point a,point b){ return point(a.x-b.x,a.y-b.y); }
inline point& operator+=(point& a,point b){ return a=a+b; }
inline point& operator-=(point& a,point b){ return a=a-b; }
inline double operator*(point a,point b){ return a.x*b.y-a.y*b.x; }
inline point operator*(point a,double b){ return point(a.x*b,a.y*b); }
inline point& operator*=(point &a,double b){ return a=a*b; }
inline point operator*(double b,point a){ return point(a.x*b,a.y*b); }
inline point operator/(point a,double b){ return point(a.x/b,a.y/b); }
inline point& operator/=(point &a,double b){ return a=a/b; }
inline double dis(point a){ return sqrt(a.x*a.x+a.y*a.y); }
inline double dis(point a,point b){ return dis(a-b); }
inline point rotate90(point a){ return point(-a.y,a.x); }
const double eps=1e-6,inf=1e30;
inline bool eq(double a,double b=0){ return fabs(a-b)<eps; }
inline bool operator==(point a,point b){ return eq(a.x,b.x)&&eq(a.y,b.y); }
inline bool operator!=(point a,point b){ return !(a==b); }
struct circle
{
	point o; double r;
	circle(point O=point(),double R=0){ o=O; r=R; }
};
inline bool operator==(circle a,circle b){ return a.o==b.o&&eq(a.r,b.r); }
inline bool operator!=(circle a,circle b){ return !(a==b); }
inline double atan(point a){ return atan2(a.y,a.x); }
std::pair<point,point> cross(circle a,circle b) // can't ensure what it will return if they have less than 2 cross points.
{
	if(a.r<b.r) std::swap(a,b);
	double d=dis(a.o,b.o),r1=a.r,r2=b.r;
	double x=sqrt(-(d-r1-r2)*(d-r1+r2)*(d+r1-r2)*(d+r1+r2))/(2*d);
	double d1=sqrt(r1*r1-x*x);
	point s=(b.o-a.o)/dis(b.o,a.o),rs=rotate90(s);
	return std::pair<point,point>(a.o+s*d1+rs*x,a.o+s*d1-rs*x);
}
inline bool in(circle a,point p){ return dis(a.o,p)<=a.r; }
inline point at(circle a,double t){ return a.o+point(a.r*cos(t),a.r*sin(t)); }
inline double &Max(double &a,double b){ return a<b?a=b:a; }
inline double &Min(double &a,double b){ return a>b?a=b:a; }
inline bool operator<(circle a,circle b){ return a.r<b.r; }
inline bool operator>(circle a,circle b){ return a.r>b.r; }
double sum(std::vector<circle> c)// works on O(n^2), the sum of n circles
{
	std::sort(c.begin(),c.end(),std::greater<circle>());
	int n=c.size(); double ans=0.;
	fr(i,0,n-1)
	{
		using P=std::pair<double,double>;
		std::vector<P> v;
		v.push_back(P(0,pi/2)); v.push_back(P(pi/2,pi*3/2)); v.push_back(P(pi*3/2,pi*2));
		int flag=c[i].r!=0;
		fr(j,0,n-1) if(c[i]==c[j]?i>j:dis(c[i].o,c[j].o)<c[j].r-c[i].r+eps) flag=0;
		if(!flag) continue;
		fr(j,0,n-1) if((c[i]!=c[j]||(c[i]==c[j]&&i<j))&&dis(c[i].o,c[j].o)+eps<c[i].r+c[j].r&&dis(c[i].o,c[j].o)+c[j].r>c[i].r+eps)
		{
			auto _p=cross(c[i],c[j]); auto p=P(atan(_p.first-c[i].o),atan(_p.second-c[i].o));
			if(p.first<-eps) p.first+=pi*2;
			if(p.second<-eps) p.second+=pi*2;
			if(p.first>p.second) std::swap(p.first,p.second);
			if(p.second-p.first<eps) continue;
			double mid=(p.first+p.second)/2;
			if(!in(c[j],at(c[i],mid))) std::swap(p.first,p.second);
			std::swap(p.first,p.second); std::vector<P> V;
			if(p.first>p.second) fr(k,0,v.size()-1)
			{
				auto _v=v[k];
				Max(_v.first,p.first); Min(_v.second,2*pi);
				if(_v.first+eps<_v.second) V.push_back(_v);
				_v=v[k];
				Max(_v.first,0); Min(_v.second,p.second);
				if(_v.first+eps<_v.second) V.push_back(_v);
			}
			else fr(k,0,v.size()-1)
			{
				auto _v=v[k];
				Max(_v.first,p.first); Min(_v.second,p.second);
				if(_v.first+eps<_v.second) V.push_back(_v);
			}
			v=V;
		}
		for(auto j:v)
		{
			auto p1=at(c[i],j.first),p2=at(c[i],j.second); int flag=0;
			double y=(p1.y-c[i].o.y)/c[i].r,Y=(p2.y-c[i].o.y)/c[i].r;
			if(j.first>pi/2-eps&&j.second<pi*3/2+eps) flag=1;
			ans+=fabs(y-Y)*c[i].r*c[i].o.x*(flag==0?1:-1);
			ans+=fabs(y*sqrt(1-y*y)+asin(y)-Y*sqrt(1-Y*Y)-asin(Y))*c[i].r*c[i].r/2;
		}
	}
	return ans;
}
typedef std::pair<point,point> line;
double dis(point a,line l){ return (l.first-a)*(l.second-a)/dis(l.first-l.second); } // not always >=0, >0 if a on the left of l
bool in(double a,double l,double r){ if(l>r) std::swap(l,r); return a>=l-eps&&a<=r+eps; }
bool in(point a,point l,point r){ return in(a.x,l.x,r.x)&&in(a.y,l.y,r.y); }
point cross(line a,line b)
{
	double d1=dis(a.first,b),d2=dis(a.second,b),t=d1/(d1-d2);
	return a.first+t*(a.second-a.first);
}
double derict(pii a)
{
	int p1=a.x>0,p2=a.y>0;
	return p1?(p2?1:4):(p2?2:3);
}
const int N=2010;
int n; std::vector<circle> c;
int main()
{
	n=read(); c.resize(n);
	fr(i,0,n-1){ c[i].o.x=read(); c[i].o.y=read(); c[i].r=read(); }
	printf("%.3lf\n",sum(c));
	return 0;
}
