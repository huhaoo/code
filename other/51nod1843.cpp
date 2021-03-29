/***************************************************************
	File name: 51nod1843.cpp
	Author: huhao
	Create time: Mon 07 Oct 2019 11:41:14 AM CST
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
const int N=110;
#define i64 long long
i64 n,p,f[N][N][N],g[N][N],G[N],C[N][N],mod,F[N];
#define add(a,b) (a=(a+(b))%mod)
int main()
{
	n=read();
	mod=read();
	fr(i,0,n)
		C[i][i]=C[i][0]=1;
	fr(i,1,n)
		fr(j,1,i-1)
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
	F[0]=1;
	fr(i,1,n)
		F[i]=F[i-1]*i%mod;
	g[1][0]=1;
	fr(i,0,n)
		fr(j,0,n)
			if(i!=j&&g[i][j])
			{
				add(g[i+1][j],g[i][j]);
				add(g[i][j+1],g[i][j]);
			}
	fr(i,1,n)
		G[i]=g[i][i]*F[i]%mod;
	f[0][0][0]=1;
	fr(i,0,n)
		fr(j,0,n)
			fr(k,0,n)
				if(f[i][j][k])
				{
					add(f[i+1][j][k],(k-i)*f[i][j][k]);
					add(f[i+1][j][k+1],(n-k)*f[i][j][k]);
					add(f[i][j+1][k],(k-j)*f[i][j][k]);
					add(f[i][j+1][k+1],(n-k)*f[i][j][k]);
					fr(d,1,n-k)
						add(f[i+d][j+d][k+d],G[d]*C[n-k][d]%mod*(mod-f[i][j][k]));
				}
	printf("%lld\n",f[n][n][n]);
	return 0;
}
