/**************************************************************
	File name: 1357.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 10/28/2018, 8:13:24 PM
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
#define N 50
#define mod 1000000007
long long __bit_cnt[N],n,m,k,ans[N],mar[N][N],c[N],cnt,p[N],a[N][N],b[N][N],s;
int main()
{
	n=read();m=read();k=read();
	fr(i,1,(1<<m)-1)__bit_cnt[i]=__bit_cnt[i&(i-1)]+1;
	fr(i,0,(1<<m)-1)if(__bit_cnt[i]<=k)c[p[i]=(++cnt)]=i;
	fr(i,1,cnt)
	{
		long long j=(c[i]&((1<<(m-1))-1))<<1;
		if(p[j])mar[p[j]][i]=1;
		if(p[j|1])mar[p[j|1]][i]=1;
	}
	fr(i,1,cnt)
	{
		fr(i,1,cnt)fr(j,1,cnt)a[i][j]=mar[i][j];
		fr(i,1,cnt)ans[i]=0;
		ans[i]=1;
		long long j=n-m;
		while(j)
		{
			if(j&1)
			{
				fr(i,1,cnt)b[i][1]=0;
				fr(i,1,cnt)fr(k,1,cnt)b[i][1]=(b[i][1]+a[i][k]*ans[k])%mod;
				fr(i,1,cnt)ans[i]=b[i][1];
			}
			j>>=1;
			fr(i,1,cnt)fr(j,1,cnt)b[i][j]=0;
			fr(i,1,cnt)fr(j,1,cnt)fr(k,1,cnt)
				b[i][j]=(b[i][j]+a[i][k]*a[k][j])%mod;
			fr(i,1,cnt)fr(j,1,cnt)a[i][j]=b[i][j];
		}
		fr(j,1,cnt)
		{
			long long o=(c[j]<<m)|c[i],f=1;
			while(o)
			{
				if(__bit_cnt[o&((1<<m)-1)]>k)f=0;
				o>>=1;
			}
			s=(s+ans[j]*f)%mod;
		}
	}
	printf("%lld\n",s);
	return 0;
}