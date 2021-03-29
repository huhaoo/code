/***************************************************************
	File name: damage.cpp
	Author: huhao
	Create time: Mon 11 Jan 2021 03:17:16 PM CST
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
const double pi=acos(-1.),eps=1e-5;
double d,l,r,t,h;
double T,q,x;
double calc(double l,double r,double (*f)(double p))
{
	double mid=(l+r)/2;
	return (f(l)+f(r)+4*f(mid))*(r-l)/6;
}
double simpson(double l,double r,double eps,double (*f)(double p))
{
	double mid=(l+r)/2;
	double f1=calc(l,r,f),f2=calc(l,mid,f),f3=calc(mid,r,f);
//	fprintf(stderr,"%.10lf %.10lf   %.10lf %.10lf %.10lf    %.10lf %.10lf\n",l,r,f1,f2,f3,f1-f2-f3,eps);
//	assert(eps>1e-15);
	if(fabs(f1-f2-f3)<eps) return f1;
	return simpson(l,mid,eps/2,f)+simpson(mid,r,eps/2,f);
}
double g(double p){ return q+p*tan(T); }
double f(double p)
{
	if(p<0) return pi-f(-p);
	return acos(p)-p*sqrt(1-p*p);
}
double F(double u,double v)
{
	if(u<-v) return pi*v*v;
	if(u>v) return 0;
	return v*v*f(u/v);
}
double f1(double p){ return F(g(p),sqrt(r*r-(x-p)*(x-p))); }
double f2(double p){ return F(g(p),d); }
double f3(double p){ return F(g(p),sqrt(r*r-(p-(l-x))*(p-(l-x)))); }
double solve(double l,double r,double (*f)(double))
{
	double ans=0,Eps=0.1;
	while(l+Eps<=r){ ans+=simpson(l,l+Eps,eps,f); l+=Eps; }
	return ans+simpson(l,r,eps,f);
}
int main()
{
	freopen("damage.in","r",stdin); freopen("damage.out","w",stdout);
	d=read()/2./100; l=read()/100.; r=read()/100.; t=read()/100.; h=read()/100.; x=sqrt(r*r-d*d);
	if(fabs(t-l)<1e-8)
	{
		printf("%.10lf\n",h*pi*d*d+simpson(x/r,1,1e-6,[](double p){ return pi*(1-p*p); })*r*r*r);
		return 0;
	}
	T=asin(t/l); q=d-h/sin(pi/2-T);
//	printf("%.10lf\n",g(0)); return 0;
	printf("%.10lf\n",solve(-(r-x)+eps,0,f1)+solve(0,l,f2)+solve(l,l+(r-x)-eps,f3));
	return 0;
}
