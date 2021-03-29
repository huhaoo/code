/**************************************************************
	File name: 2503.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/12/2018, 7:40:15 PM
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
#define N 30
int n,a[N],b[N],m,c[N];
double T,eps=1e-18,k=0.99,x,lst,ans;
double calc()
{
	double sum=0;
	fr(i,1,m)c[i]=0;
	fr(i,1,n)c[b[i]]+=a[i];
	fr(i,1,m)sum+=(1.*c[i]-x)*(1.*c[i]-x);
	return sqrt(sum/(1.*m));
}
#include<stdlib.h>
int main()
{
	srand(19260817);
	n=read();
	m=read();
	fr(i,1,n)
		a[i]=read(),x+=1.*a[i];
	x/=1.*m;
	ans=1e20;
	fr(_,1,1000)
	{
		fr(i,1,n)b[i]=rand()%m+1;
		lst=calc();
		T=1;
		while(T>eps)
		{
			int pos=rand()%n+1,w=rand()%m+1;
			int l=b[pos];
			b[pos]=w;
			double c=calc();
			if(exp(1.*(lst-c)/T)*RAND_MAX>rand()*1.)
				lst=c,ans=min(ans,c);
			else
				b[pos]=l;
			T*=k;
		}
	}
	printf("%.2lf",ans);
	return 0;
}