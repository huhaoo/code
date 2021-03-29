/**************************************************************
	File name: 3980.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/10/2018, 3:23:33 PM
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
#define N 10010
#define M 1010
#define eps 1e-8
int n,m;
double a[M][N];//a[1..m][1..n]
void pivot(int l,int e)
{
	double k=a[l][e];a[l][e]=1.0;
	fr(i,0,n)a[l][i]/=k;
	fr(i,0,m)
		if(i!=l&&fabs(a[i][e])>eps)
		{
			k=a[i][e];a[i][e]=0;
			fr(j,0,n)
				a[i][j]-=a[l][j]*k;
		}
}
int init()
{
	while(1)
	{
		int l=0,e=0;
		fr(i,1,m)
			if(a[i][0]<-eps&&(!l||(rand()%3)))
				l=i;
		if(!l)
			break;
		fr(i,1,n)
			if(a[l][i]<-eps&&(!e||rand()%3))
				e=i;
		if(!e)
			return 0;
		pivot(l,e);
	}
	return 1;
}
int simplex()
{
	while(1)
	{
		int l=0,e=0;
		double mi=1e15;
		fr(i,1,n)
			if(a[0][i]>eps)
			{
				e=i;
				break;
			}
		if(!e)
			break;
		fr(i,1,m)
			if(a[i][e]>eps&&a[i][0]/a[i][e]<mi)
			{
				mi=a[i][0]/a[i][e];
				l=i;
			}
		if(!l)return 0;
		pivot(l,e);
	}
	return 1;
}
#include<stdlib.h>
int main()
{
	srand((unsigned long long)new char);
	m=read();
	n=read();
	fr(i,1,m)a[i][0]=-1.0*read();
	fr(i,1,n)
	{
		fr(j,read(),read())
			a[j][i]=-1.0;
		a[0][i]=-1.0*read();
	}
//	fr(i,0,m)
//		fr(j,0,n)
//			printf("%d%c",int(a[i][j]),j==n?'\n':' ');
	init();
	simplex();
	printf("%d\n",int(a[0][0]));
	return 0;
}