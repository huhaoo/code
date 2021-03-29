/***************************************************************
	File name: H.cpp
	Author: huhao
	Create time: Thu 07 Jan 2021 03:28:45 PM CST
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
const int N=1010;
int n;
double w,h;
double g[N],f[N];
double sqr(double a){ return a*a; }
int main()
{
	w=read(); h=read(); n=read(); h/=w;
	f[0]=sqr((1+h)/2);
	fr(i,1,n)
	{
		double a=f[i-1]+sqr(h-1)/4-sqr(h)/2,b=(h+1)*(h-1)/2,c=sqr(h+1)/4;
//		printf("%.10lf %.10lf %.10lf\n",a,b,c);
		g[i]=-b/(2*a); f[i]=(a*g[i]+b)*g[i]+c;
	}
//	fr(i,0,n) printf("%.10lf %.10lf\n",f[i],g[i]);
	fd(i,n-1,1) g[i]*=g[i+1];
	printf("%.10lf\n",f[n]*w*w);
	fr(i,1,std::min(n,10)) printf("%.10lf\n",g[i]*w);
	return 0;
}
