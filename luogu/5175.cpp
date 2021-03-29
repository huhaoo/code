/**************************************************************
	File name: 5175.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 1/7/2019, 3:29:53 PM
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
#define mod 1000000007
#define N 10
long long T,n,a[N][N],ans[N][N],o[N][N],a1,a2,x,y,r[N][N];
void times(long long a[N][N],long long b[N][N],long long c,long long d,long long e)
{
	fr(i,1,c)
		fr(j,1,e)
		{
			r[i][j]=0;
			fr(k,1,d)
				r[i][j]=(r[i][j]+a[i][k]*b[k][j])%mod;
		}
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		a1=read();
		a2=read();
		x=read();
		y=read();
		fr(i,1,4)
			fr(j,1,4)
				a[i][j]=0;
		fr(i,1,4)
			ans[i][1]=0;
		a[1][2]=1;
		a[2][1]=y*y%mod;
		a[2][2]=x*x%mod;
		a[2][3]=2*x*y%mod;
		a[3][2]=x;
		a[3][3]=y;
		a[4][1]=1;
		a[4][4]=1;
		ans[1][1]=a1*a1%mod;
		ans[2][1]=a2*a2%mod;
		ans[3][1]=a1*a2%mod;
		while(n)
		{
			if(n&1)
			{
				times(a,ans,4,4,1);
				fr(i,1,4)
					ans[i][1]=r[i][1];
			}
			times(a,a,4,4,4);
			fr(i,1,4)
				fr(j,1,4)
					a[i][j]=r[i][j];
			n>>=1;
		}
/*		fr(i,1,4)
			printf("%lld%c",ans[i][1],i==4?'\n':' ');
		fr(i,1,n)
		{
			times(a,ans,4,4,1);
			fr(j,1,4)
			{
				ans[j][1]=r[j][1];
				printf("%lld%c",ans[j][1],j==4?'\n':' ');
			}
		}*/
/*		fr(i,1,4)
			fr(j,1,4)
				printf("%lld%c",a[i][j],j==4?'\n':' ');*/
		printf("%lld\n",ans[4][1]);
	}
	return 0;
}
//1 1 2 3 5