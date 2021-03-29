/***************************************************************
	File name: 4221.cpp
	Author: huhao
	Create time: Mon 30 Sep 2019 01:56:44 PM CST
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
#define i64 long long
const int N=25,M=(1<<21)|10;
const i64 mod=998244353;
i64 n,m,p,c[M],C,a[N][N],w[N],W[M],f[N],b[N],B,id[M],d[N],iW[M],F[N][M],G[N][M],l[N];
int getf(int x)
{
	return x==f[x]?x:f[x]=getf(f[x]);
}
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	a%=p;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
void fwt(i64 *a,int opt)
{
	fr(i,0,n-1)
		for(int j=0;j<(1<<n);j+=(1<<(i+1)))
			fr(k,0,(1<<i)-1)
				a[j+k+(1<<i)]=(a[j+k]*opt+a[j+k+(1<<i)]+mod)%mod;
}
int main()
{
	n=read();
	m=read();
	p=read();
	fr(i,1,m)
	{
		int u=read(),v=read();
		a[u][v]=a[v][u]=1;
	}
	fr(i,1,n)
		w[i]=read();
	fr(i,1,n)
		id[(1<<(i-1))]=i;
	fr(i,1,(1<<n)-1)
	{
		int flag=1;
		W[i]=W[i-(i&(-i))]+w[id[i&(-i)]];
		B=0;
		for(int j=i;j;j-=(j&(-j)))
			b[++B]=id[j&(-j)];
		fr(j,1,B)
		{
			f[j]=j;
			d[j]=0;
		}
		fr(j,1,B)
			fr(k,j+1,B)
				if(a[b[j]][b[k]])
				{
					f[getf(j)]=getf(k);
					d[j]++;
					d[k]++;
				}
		fr(i,2,B)
			if(getf(i)!=getf(1))
				flag=0;
		fr(i,1,B)
			if(d[i]%2!=0)
				flag=0;
		if(flag)
			continue;
		c[++C]=i;
	}
	fr(i,1,(1<<n)-1)
	{
		W[i]=power(W[i],p,mod);
		iW[i]=power(W[i],mod-2,mod);
	}
	fr(i,1,(1<<n)-1)
		l[i]=l[i-(i&(-i))]+1;
	fr(i,1,C)
		G[l[c[i]]][c[i]]=W[c[i]];
	fr(i,1,n)
		fwt(G[i],1);
	F[0][0]=1;
	fwt(F[0],1);
	fr(i,1,n)
	{
		fr(j,0,i-1)
			fr(k,0,(1<<n)-1)
				F[i][k]=(F[i][k]+F[j][k]*G[i-j][k])%mod;
		fwt(F[i],-1);
		fr(j,0,(1<<n)-1)
			F[i][j]=F[i][j]*iW[j]%mod;
		fwt(F[i],1);
	}
	fwt(F[n],-1);
	printf("%lld\n",F[n][(1<<n)-1]);
	return 0;
}
