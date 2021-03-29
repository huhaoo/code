/****************************************************************
	File name: 3389.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 11/9/2018, 7:59:03 PM
****************************************************************/
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
#define N 110
#define eps (1e-8)
int n;
double a[N][N];
int calc()
{
	fr(i,1,n)
	{
		int k=i;
		fr(j,i+1,n)if(fabs(a[j][i])-fabs(a[k][i])>eps)
			k=j;
		if(fabs(a[k][i])<eps)
			return 0;
		fr(j,i,n+1)
			swap(a[i][j],a[k][j]);
		fr(j,i+1,n+1)
			a[i][j]/=a[i][i];
		a[i][i]=1;
		fr(j,i+1,n)
		{
			fr(k,i+1,n+1)
				a[j][k]-=a[i][k]*a[j][i];
			a[j][i]=0;
		}
	}
	fd(i,n,1)fr(j,i+1,n)
		a[i][n+1]-=a[i][j]*a[j][n+1];
	return 1;
}
int main()
{
	n=read();
	fr(i,1,n)fr(j,1,n+1)
		a[i][j]=(double)read();
	if(!calc())
		printf("No Solution\n");
	else
		fr(i,1,n)
			printf("%.2lf\n",a[i][n+1]);
	return 0;
}