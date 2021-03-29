/**************************************************************
	File name: 3268.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/24/2018, 3:33:05 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
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
#define N 400010
#define eps 1e-8
#include<set>
long long n,x[N],y[N],r[N],xx,ans,op[N];
struct cir
{
	long long t,p;
	cir(long long tt=0,long long pp=0){t=tt;p=pp;}
	double calc(){return sqrt(r[p]*r[p]-(xx-x[p])*(xx-x[p]))+eps;}
};
set<cir>s;
bool operator<(cir a,cir b)
{
	return double(y[a.p])+a.t*a.calc()+eps<double(y[b.p])+b.t*b.calc();
}
struct point
{
	long long t,p,v;
	point(long long tt=0,long long pp=0,long long vv=0){t=tt;p=pp;v=vv;}
}p[N];
int main()
{
	n=read();
	fr(i,1,n)
	{
		x[i]=read();y[i]=read();r[i]=read();
		p[i*2-1]=point(1,i,x[i]-r[i]);
		p[i*2]=point(-1,i,x[i]+r[i]);
	}
	sort(p+1,p+2*n+1,[&](point a,point b){return a.v<b.v;});
	fr(i,1,2*n)
	{
		xx=p[i].v;
		if(p[i].t==1)
		{
			auto it=s.insert(cir(1,p[i].p)).first;
			if(s.begin()==it)
				op[p[i].p]=1;
			else
			{
				it--;
				if((*it).t==-1)op[p[i].p]=-op[(*it).p];
				else op[p[i].p]=op[(*it).p];
			}
			ans+=op[p[i].p]*r[p[i].p]*r[p[i].p];
//			printf("%lld %lld\n",p[i].p,op[p[i].p]);
			s.insert(cir(-1,p[i].p));
		}
		else
		{
			s.erase(cir(1,p[i].p));
			s.erase(cir(-1,p[i].p));
		}
	}
	printf("%lld\n",ans);
	return 0;
}