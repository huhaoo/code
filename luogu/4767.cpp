/***************************************************************
	File name: 4767.cpp
	Author: huhao
	Create time: Thu 26 Sep 2019 10:37:04 AM CST
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
const int N=3010,inf=1e9;
int n,m,a[N],c[N][N],f[N][N],s[N][N];
int main()
{
	n=read();
	m=read();
	fr(i,1,n)
		a[i]=read();
	fr(i,1,n)
	{
		int l=i,r=i,s=0;
		while(l>1&&r<n)
		{
			l--;
			r++;
			s+=a[r]-a[i]+a[i]-a[l];
			c[l][r]=s;
		}
		l=i;
		r=i+1;
		s=a[r]-a[i];
		c[l][r]=s;
		while(l>1&&r<n)
		{
			l--;
			r++;
			s+=a[r]-a[i]+a[i]-a[l];
			c[l][r]=s;
		}
	}
	fr(i,0,n)
		fr(j,0,m)
			f[i][j]=inf;
	f[0][0]=0;
	fr(j,1,m)
		fd(i,n,1)
		{
			fr(k,j==1?0:s[i][j-1],i==n?n:s[i+1][j])
				if(f[k][j-1]+c[k+1][i]<f[i][j])
				{
					f[i][j]=f[k][j-1]+c[k+1][i];
					s[i][j]=k;
				}
		}
	printf("%d\n",f[n][m]);
	return 0;
}
