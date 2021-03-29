/**************************************************************
	File name: 1337.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/12/2018, 4:41:23 PM
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
#define N 1010
int n;
double x[N],y[N],w[N],xx,yy,T,k,eps,ansx,ansy,anss;
double calc(double xx,double yy)
{
	double sum=0.0;
	fr(i,1,n)
		sum+=sqrt((x[i]-xx)*(x[i]-xx)+(y[i]-yy)*(y[i]-yy))*w[i];
	return sum;
}
#include<stdlib.h>
int main()
{
//	srand((unsigned long long )new char);
	srand(19240817);
	n=read();
	fr(i,1,n)
		x[i]=1.*read(),y[i]=1.*read(),w[i]=1.*read();
	xx=yy=0.;
	T=1.;
	k=0.99;
	eps=1e-18;
	anss=calc(0.,0.);
	while(T>eps)
	{
		double x=xx+(rand()*2ll-RAND_MAX)*T,y=yy+(rand()*2ll-RAND_MAX)*T;
//		x=0.577,y=1.;
		double d1=calc(x,y),d2=calc(xx,yy),d=d2-d1;
		if(d>0)
		{
			xx=x;
			yy=y;
			if(d1<anss)
			{
				anss=d1;
				ansx=xx;
				ansy=yy;
			}
		}
		else if(exp(d/T)*RAND_MAX>rand()*1.)
			xx=x,yy=y;
		T*=k;
	}
	printf("%.3lf %.3lf\n",ansx,ansy);
	return 0;
}