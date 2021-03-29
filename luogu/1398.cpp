/***************************************************************
	File name: 1398.cpp
	Author: huhao
	Create time: Sun 23 Jun 2019 07:18:13 PM CST
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
const int N=510,inf=(1<<29);
int n,m,w[N][N],s[N][N],a[N][N],b[N][N],c[N][N],d[N][N],e[N][N],f[N],g[N][N],h[N],o[N][N],p[N][N],q[N][N],ans;
int main()
{
	n=read();
	m=read();
	fr(i,1,n)
		fr(j,1,m)
		{
			w[i][j]=read();
			s[i][j]=s[i-1][j]+w[i][j];
		}
	fr(i,0,n)
		fr(j,0,n)
			a[i][j]=b[i][j]=e[i][j]=g[i][j]=o[i][j]=p[i][j]=q[i][j]=-inf;
	fr(i,0,m)
		f[i]=h[i]=-inf;
	fr(i,1,m)
	{
		fr(j,0,n)
			fr(k,0,n)
				c[j][k]=d[j][k]=-inf;
		fr(j,1,n)
			fr(k,j,n)
				c[j][k]=b[j][k];
		fr(j,1,n)
			fr(k,j,n)
				b[j][k]=-inf;
		fr(j,2,n)
		{
			int x=c[j][j];
			fd(k,j-1,1)
			{
				e[k][j]=max(e[k][j],x)+s[j][i]-s[k-1][i];
				f[i]=max(f[i],e[k][j]);
				x=max(x,c[k][j]);
			}
		}
		fd(j,n-1,1)
		{
			int x=a[j][n];
			fd(k,n-1,j)
			{
				b[j][k]=x+s[k][i]-s[j-1][i];
				x=max(x,a[j][k]);
			}
		}
		fr(j,1,n)
		{
			d[1][j]=c[1][j];
			fr(k,2,j)
				d[k][j]=max(d[k-1][j],c[k][j]);
		}
		fr(j,1,n)
		{
			int x=j==1?-inf:d[j-1][j-1];
			fr(k,j,n)
			{
				x=max(x,d[j][k]);
				b[j][k]=max(b[j][k],x+s[k][i]-s[j-1][i]);
			}
		}
		fr(j,1,n)
			fr(k,j,n)
				a[j][k]=max(a[j][k],0)+s[k][i]-s[j-1][i];
	}
	fr(i,2,m)
		f[i]=max(f[i],f[i-1]);
	fr(i,4,m-1)
	{
		fr(j,1,n)
			fr(k,j+2,n)
			{
				g[j][k]=max(g[j][k],f[i-3]+s[k][i-1]-s[j-1][i-1])+w[j][i]+w[k][i];
				h[i+1]=max(h[i+1],g[j][k]+s[k][i+1]-s[j-1][i+1]);
			}
	}
	fr(i,2,m)
		h[i]=max(h[i],h[i-1]);
	ans=-inf;
	fr(i,3,m)
	{
		fr(j,1,n)
			fr(k,j+2,n)
			{
				q[j][k]=max(q[j][k],p[j][k])+w[j][i]+w[k][i];
				ans=max(ans,q[j][k]);
			}
		fr(j,1,n)
			fr(k,j+2,n)
				p[j][k]=max(p[j][k],o[j][k])+s[k][i]-s[j-1][i];
		fr(j,1,n)
			fr(k,j+2,n)
				o[j][k]=max(o[j][k],h[i-2])+w[j][i]+w[k][i];
	}
	printf("%d\n",ans);
	return 0;
}
