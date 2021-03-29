/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Sat 28 Nov 2020 04:45:41 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
#define i64 long long
const int N=8000010,mod=1000000007,M=2010;
i64 f[N],F[N],n,m;
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 C(i64 a,i64 b){ return a>=b&&b>=0?f[a]*F[b]%mod*F[a-b]%mod:0; }
i64 c(i64 a,i64 b){ return C(a+b,b); }
i64 ans,g[M][M],s[M][M];
void Add(i64 &a,i64 b){ a=(a+b)%mod; }
int main()
{
	n=N-10;
	f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
	F[n]=power(f[n],mod-2); fd(i,n,1) F[i-1]=F[i]*i%mod;
	n=read(); m=read()-1;
	if(!m){ printf("1\n"); return 0; }
	g[1][1]=f[n];
	fr(i,1,n)
	{
		fd(j,i,1) Add(g[i][j],g[i][j+1]);
		fd(j,i,1) g[i][j]=g[i][j]*c((i-1)*(m+1)-(j-1),m-1)%mod;
		fr(j,1,i) Add(g[i+1][j+1],g[i][j]);
	}
//	memset(g,0,sizeof(g)); g[0][0]=f[n];
//	fr(i,0,n-1) fr(j,0,i) fr(k,0,j) Add(g[i+1][k+1],g[i][j]*c(i*(m+1)-k,m-1));
//	fr(i,0,n) fr(j,0,i) printf("%lld%c",g[i][j],j==i?'\n':' ');
	fr(i,0,n) Add(ans,g[n][i]);
	printf("%lld\n",ans);
	return 0;
}
