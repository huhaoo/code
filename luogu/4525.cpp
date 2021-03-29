/**************************************************************
	File name: 4525.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 6/2/2018, 9:17:46 AM
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
double a,b,c,d,l,r;
double f(double x)
{
	return (c*x+d)/(a*x+b);
}
double calc(double l,double r)
{
	double mid=(l+r)/2;
	return (r-l)*(f(l)+f(r)+4*f(mid))/6;
}
double integral(double l,double r,double f1,double eps)
{
	double mid=(l+r)/2;
	double f2=calc(l,mid),f3=calc(mid,r);
	if(fabs(f1-f2-f3)<=eps)return f1;
	else return integral(l,mid,f2,eps/2)+integral(mid,r,f3,eps/2);
}
int main()
{
	scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&l,&r);
	printf("%.6lf",integral(l,r,calc(l,r),1e-8));
	return 0;
}
