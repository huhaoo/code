/***************************************************************
	File name: 4254.cpp
	Author: huhao
	Create time: Thu 19 Sep 2019 11:37:51 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
const int N=200010;
const double inf=1e-10;
int q,n=50000,p[N];
double a[N],b[N];
void modify(int k,int l,int r,double A,double B)
{
	if(!p[k])
	{
		p[k]=1;
		a[k]=A;
		b[k]=B;
		return;
	}
	int mid=(l+r)>>1;
	double f1=a[k]*mid+b[k],f2=A*mid+B;
	if(f2>f1)
	{
		if(l!=r)
		{
			if(a[k]<A)
				modify(k<<1,l,mid,a[k],b[k]);
			else
				modify(k<<1|1,mid+1,r,a[k],b[k]);
		}
		a[k]=A;
		b[k]=B;
	}
	else if(l!=r)
	{
		if(A<a[k])
			modify(k<<1,l,mid,A,B);
		else
			modify(k<<1|1,mid+1,r,A,B);
	}
}
double query(int k,int l,int r,int v)
{
	if(!p[k])
		return -inf;
	double f=a[k]*v+b[k];
	if(l==r)
		return f;
	int mid=(l+r)>>1;
	if(v<=mid)
		return max(f,query(k<<1,l,mid,v));
	else
		return max(f,query(k<<1|1,mid+1,r,v));
}
int main()
{
	q=read();
	while(q--)
	{
		char s[20];
		scanf("%s",s);
		if(*s=='P')
		{
			double A,B;
			scanf("%lf%lf",&B,&A);
			B-=A;
			modify(1,1,n,A,B);
		}
		else
		{
			int p=read();
			printf("%lld\n",(long long)(query(1,1,n,p))/100);
		}
	}
	return 0;
}
