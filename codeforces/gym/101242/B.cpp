/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Wed 06 Jan 2021 02:34:07 PM CST
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
const int N=5010,inf=1000000000;
int n,a[N][N],d[N],D[N],vis[N],e,m,k;
i64 f[N][N],s[N]; int p[N][N];
int main()
{
	n=read(); m=read(); k=read(); e=read();
	fr(i,1,n) fr(j,1,n) a[i][j]=inf;
	fr(i,1,e){ int u=read(),v=read(); a[u][v]=read(); }
	fr(i,1,n){ d[i]=inf; vis[i]=0; }
	d[m+1]=0;
	fr(i,1,n)
	{
		int u=0;
		fr(j,1,n) if(!vis[j]&&(!u||d[j]<d[u])) u=j;
		vis[u]=1;
		fr(j,1,n) d[j]=std::min(d[u]+a[u][j],d[j]);
	}
	fr(i,1,n){ D[i]=inf; vis[i]=0; }
	D[m+1]=0;
	fr(i,1,n)
	{
		int u=0;
		fr(j,1,n) if(!vis[j]&&(!u||D[j]<D[u])) u=j;
		vis[u]=1;
		fr(j,1,n) D[j]=std::min(D[u]+a[j][u],D[j]);
	}
	n=m; m=k;
	fr(i,1,n) s[i]=d[i]+D[i];
	std::sort(s+1,s+n+1);
	fr(i,1,n) s[i]+=s[i-1];
	fr(i,1,n){ f[1][i]=s[i]*(i-1); p[1][i]=0; }
	fr(i,1,n) p[i][n+1]=n;
//	fr(i,1,n) printf("%lld%c",s[i],i==n?'\n':' ');
	fr(i,2,n) fd(j,n,1)
	{
		f[i][j]=(i64)inf*inf;
		fr(u,p[i-1][j],p[i][j+1])
			if(f[i][j]>f[i-1][u]+(s[j]-s[u])*(j-u-1))
			{
				f[i][j]=f[i-1][u]+(s[j]-s[u])*(j-u-1);
				p[i][j]=u;
			}
//		printf("%d %d  %d %lld\n",i,j,p[i][j],f[i][j]);
	}
	printf("%lld\n",f[m][n]);
	return 0;
}
