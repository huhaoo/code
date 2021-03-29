/***************************************************************
	File name: 生成树计数.cpp (hdu 4305)
	Author: huhao
	Create time: Wed 15 Jan 2020 02:10:42 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=310,mod=10007;
namespace tree_counter
{
#define i64 long long
	i64 power(i64 a,i64 b,i64 p)
	{
		i64 r=1;
		while(b)
		{
			if(b&1) r=r*a%p;
			a=a*a%p; b>>=1;
		}
		return r;
	}
	i64 inv(i64 a){ return power(a,mod-2,mod); }
	i64 a[N][N];
	i64 solve(int A[N][N],int n)
	{
		fr(i,1,n) fr(j,1,n) a[i][j]=-A[i][j];
		fr(i,1,n) fr(j,1,n) if(i!=j) a[i][i]-=a[i][j];
//		fr(i,1,n) fr(j,1,n) printf("%lld%c",a[i][j],j==n?'\n':' ');
		i64 ans=1; n--;
		fr(i,1,n)
		{
			i64 k=inv(a[i][i]); ans=ans*a[i][i]%mod;
			fr(j,i,n) a[i][j]=a[i][j]*k%mod;
			fr(j,i+1,n)
			{
				k=a[j][i];
				fr(l,i,n) a[j][l]=(a[j][l]-a[i][l]*k)%mod;
			}
		}
		return (ans%mod+mod)%mod;
	}
}
int n,a[N][N],r,f[N],x[N],y[N];
int getf(int u){ return u==f[u]?u:getf(f[u]); }
int main()
{
	fr(T,1,read())
	{
		n=read(); r=read();
		fr(i,1,n) fr(j,1,n) a[i][j]=0;
		fr(i,1,n) f[i]=i;
		fr(i,1,n){ x[i]=read(); y[i]=read(); }
		fr(i,1,n) fr(j,i+1,n) if((x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])<=r*r)
		{
			int flag=1;
			fr(k,1,n) if(k!=i&&k!=j&&((x[i]>x[k]&&x[j]<x[k])||(x[i]<x[k]&&x[j]>x[k]))&&(x[k]-x[i])*(y[j]-y[i])-(y[k]-y[i])*(x[j]-x[i])==0) flag=0;
			if(flag){ a[i][j]=a[j][i]=1; f[getf(i)]=getf(j); }
		}
		int flag=1;
		fr(i,2,n) if(getf(i)!=getf(1)) flag=0;
		printf("%lld\n",flag?tree_counter::solve(a,n):-1);
	}
	return 0;
}
