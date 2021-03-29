/**************************************************************
	File name: 4238.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/5/2018, 7:25:27 PM
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
#define N (1<<20)
long long power(long long x,long long y,long long p)
{
	long long r=1;
	while(y)
	{
		if(y&1)r=r*x%p;
		x=x*x%p;
		y>>=1;
	}
	return r;
}
long long n,a[N],b[N],c[N],ans[N],mod=998244353,g=3,gp=power(g,mod-2,mod),l,r[N];
void NTT(long long *a,long long opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		long long wn=power(opt==1?g:gp,(mod-1)>>(i+1),mod);
		for(long long j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			long long w=1;
			fr(k,0,(1<<i)-1)
			{
				long long x=a[j+k],y=w*a[(1<<i)+j+k]%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+(1<<i)]=(x-y+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
	if(opt==-1)
	{
		long long inv=power((1<<l),mod-2,mod);
		fr(i,0,(1<<l)-1)
			a[i]=a[i]*inv%mod;
	}
}
void inv(long long *a,long long *b,long long n)
{
	if(n==1){b[0]=power(a[0],mod-2,mod);return;}
	inv(a,b,(n+1)>>1);
	l=0;
	while((1<<l)<=(n<<1))l++;
	fr(i,0,(1<<l)-1)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,0,n-1)c[i]=a[i];
	fr(i,n,(1<<l)-1)c[i]=0;
	NTT(b,1);NTT(c,1);
	fr(i,0,(1<<l)-1)b[i]=(2*b[i]%mod-b[i]*b[i]%mod*c[i]%mod+mod)%mod;
	NTT(b,-1);
	fr(i,n,(1<<l)-1)b[i]=0;
}
int main()
{
	n=read();
	fr(i,0,n-1)a[i]=read();
	inv(a,b,n);
	fr(i,0,n-1)printf("%lld%c",b[i],i==n-1?'\n':' ');
	return 0;
}