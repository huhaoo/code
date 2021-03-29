/**************************************************************
	File name: 4721.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/22/2018, 8:44:17 AM
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
#define mod 998244353
#define g 3
#define gp 332748118
#define N 400010
long long f[N],a[N],r[N],l,n,x[N],y[N],z[N];
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
void NTT(long long *a,long long opt)
{
	fr(i,0,(1<<l)-1)if(i<r[i])swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		long long wn=power(opt==1?g:gp,(mod-1)>>(i+1),mod);
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			long long w=1;
			fr(k,0,(1<<i)-1)
			{
				long long x=a[j+k],y=w*a[j+k+(1<<i)]%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+(1<<i)]=(x-y+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
	if(opt==-1)
	{
		long long k=power((1<<l),mod-2,mod);
		fr(i,0,(1<<l)-1)a[i]=a[i]*k%mod;
	}
}
void cdq(long long ll,long long rr)
{
	if(ll==rr)return;
	long long m=(ll+rr)>>1;
	cdq(ll,m);
	l=0;
	while((1<<l)<=(rr-ll+1)*2)l++;
	fr(i,0,(1<<l)-1)x[i]=y[i]=0,r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,ll,m)x[i-ll]=f[i];
	fr(i,0,rr-ll)y[i]=a[i];
//	printf("- %lld %lld %lld\n",ll,rr,m);
//	fr(i,ll,m)printf("%lld%c",x[i-ll],i==m?'\n':' ');
//	fr(i,0,rr-ll)printf("%lld%c",y[i],i==rr-ll?'\n':' ');
	NTT(x,1);NTT(y,1);
	fr(i,0,(1<<l)-1)z[i]=x[i]*y[i]%mod;
	NTT(z,-1);
//	fr(i,0,(1<<l)-1)printf("%lld%c",z[i],i==(1<<l)-1?'\n':' ');
	fr(i,m+1,rr)f[i]=(f[i]+z[i-ll])%mod;
	cdq(m+1,rr);
}
int main()
{
	n=read();
	fr(i,1,n-1)a[i]=read();
	f[0]=1;
	cdq(0,n-1);
	fr(i,0,n-1)printf("%lld%c",f[i],i==n-1?'\n':' ');
	return 0;
}