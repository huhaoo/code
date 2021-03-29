/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Thu 07 Jan 2021 08:50:20 AM CST
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
#define point std::pair<double,double>
#define x first
#define y second
const int N=50010;
int n,m;
point p[N],P[N];
double d[N],D[N];
double dis(point a){ return sqrt(a.x*a.x+a.y*a.y); }
point operator*(point a,double b){ return {a.x*b,a.y*b}; }
point operator/(point a,double b){ return a*(1./b); }
point operator+(point a,point b){ return {a.x+b.x,a.y+b.y}; }
point operator-(point a,point b){ return a+b*(-1); }
double operator*(point a,point b){ return a.x*b.y-a.y*b.x; }
double calc(point a,point b)
{
	double d1=dis(a),d2=dis(b),d3=dis(a-b),d=fabs(a*b)/d3;
	double ans=std::min(d1,d2);
	if(fabs(d3-sqrt(d1*d1-d*d)-sqrt(d2*d2-d*d))<1e-8) ans=std::min(ans,d);
//	printf("%.10lf %.10lf  %.10lf %.10lf   %.10lf\n",a.x,a.y,b.x,b.y,ans);
	return ans;
}
bool check(double t)
{
	int i=1,j=1; double I=0,J=t;
	while(D[j]<=J){ J-=D[j]; j++; }
	while(i!=n&&j!=m)
	{
		double k=std::min(d[i]-I,D[j]-J);
		point di=p[i+1]-p[i],dj=P[j+1]-P[j];
		di=di/dis(di); dj=dj/dis(dj);
		if(calc((p[i]+di*I)-(P[j]+dj*J),(p[i]+di*(I+k))-(P[j]+dj*(J+k)))-t<1e-8) return 1;
		I+=k; J+=k;
//		fprintf(stderr,"%d %d  %.10lf %.10lf  %.10lf %.10lf  %.10lf\n",i,j,I,J,d[i]-I,D[j]-J,k);
		if(d[i]-I<1e-8){ i++; I=0; }
		if(D[j]-J<1e-8){ j++; J=0; }
	}
	return 0;
}
int main()
{
	n=read();
	fr(i,1,n){ p[i].x=read(); p[i].y=read(); }
	m=read();
	fr(i,1,m){ P[i].x=read(); P[i].y=read(); }
	double l=0,r=0;
	fr(i,1,n-1) d[i]=dis(p[i]-p[i+1]);
	fr(i,1,m-1) D[i]=dis(P[i]-P[i+1]);
	fr(i,1,m-1) r+=D[i];
	if(dis(P[m]-p[1])>r){ printf("impossible\n"); return 0; }
	while(r-l>1e-7)
	{
		double mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%.10lf\n",l);
	return 0;
}
