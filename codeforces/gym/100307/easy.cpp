/***************************************************************
	File name: easy.cpp
	Author: huhao
	Create time: Thu 19 Nov 2020 04:05:28 PM CST
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
#include<vector>
const int N=400010;
const double eps=2e-6;
int n;
double x[N],y[N],mx,Mi[N],Mx[N];
double calc(double x,double y,double X,double Y,double p){ return y+(Y-y)*(p-x)/(X-x); }
std::vector<double> ans(4);
#define P std::pair<double,double>
#include<map>
std::map<double,P> m;
P solve(double p)
{
	if(m.count(p)) return m[p];
	static double s[N]; int t=0;
	fr(i,0,n-1)
	{
		int v=(i?i-1:n-1),u=i;
		if(x[v]<x[u]) std::swap(u,v);
		if(x[u]<=p&&p<x[v]) s[t++]=calc(x[u],y[u],x[v],y[v],p);
		else
		{
			if(Mi[i]>p||Mx[i]<=p) i+=7;
		}
		if(t==2) break;
	}
	if(s[0]>s[1]) std::swap(s[0],s[1]);
//	printf("%.5lf  %.5lf %.5lf\n",p,mi,mx);
	return m[p]=P(s[0],s[1]);
}
double calc(double p,double q)
{
	P a=solve(p),b=solve(q);
	double l=std::max(a.first,b.first),r=std::min(a.second,b.second);
	if(l+eps>r) return 0;
	ans={p,l,q,r};
	return (q-p)*(r-l);
}
double calc(double q)
{
	double l=q,r=mx;
	while(r-l>eps)
	{
		double m=(l+r)/2;
		if(calc(q,m)>eps) l=m;
		else r=m;
	}
	r=l; l=q;
	while(r-l>eps)
	{
		double p=(r-l)/3;
		if(calc(q,l+p)<calc(q,r-p)) l+=p;
		else r-=p;
	}
	return calc(q,l);
}
int main()
{
	freopen("easy.in","r",stdin); freopen("easy.out","w",stdout);
	n=read();
	fr(i,0,n-1){ x[i]=read(); y[i]=read(); }
	double l=x[0],r=x[0];
	fr(i,1,n-1){ l=std::min(l,x[i]); r=std::max(r,x[i]); }
	mx=r;
	fr(i,0,n-1)
	{
		Mx[i]=Mi[i]=x[i];
		fr(j,1,8){ Mx[i]=std::max(Mx[i],x[(i+j)%n]); Mi[i]=std::min(Mi[i],x[(i+j)%n]); }
	}
	while(r-l>eps)
	{
		double p=(r-l)/3;
		if(calc(l+p)<calc(r-p)) l+=p;
		else r-=p;
	}
//	printf("%.10lf\n",calc(l));
	fr(i,0,3) printf("%.10lf%c",ans[i],i==3?'\n':' ');
	return 0;
}
