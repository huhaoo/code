/***************************************************************
	File name: 3711.cpp
	Author: huhao
	Create time: Thu 16 Apr 2020 04:37:08 PM CST
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
#include<vector>
#define i64 long long
#define poly std::vector<i64>
#define pii std::pair<i64,i64>
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
const int mod=998244353;
i64 inv(i64 a){ return power(a,mod-2,mod); }
const int g=3,G=inv(g),N=(1<<20)|10;
inline i64 Mod(i64 a){ return a>=mod?a-mod:a; }
inline i64 &Add(i64 &a,i64 b){ return a=(a+b)%mod; }
i64 r[N],l,w[N];
void init(int n)
{
	l=0;
	while((1<<l)<n) l++;
	fr(i,0,(1<<l)-1) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	w[0]=1; w[1]=power(g,(mod-1)>>l,mod);
	fr(i,2,(1<<l)) w[i]=w[i-1]*w[1]%mod;
}
void NTT(i64 *a,i64 opt)
{
	fr(i,0,(1<<l)-1) if(i<r[i]) std::swap(a[i],a[r[i]]);
	fr(i,0,l-1) for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
	{
		i64 x=a[j+k],y=a[j+k+(1<<i)]*w[opt==1?(k<<(l-i-1)):(1<<l)-(k<<(l-i-1))]%mod;
		a[j+k]=Mod(x+y); a[j+k+(1<<i)]=Mod(x-y+mod);
	}
	if(opt==-1)
	{
		i64 I=inv(1<<l);
		fr(i,0,(1<<l)-1) a[i]=a[i]*I%mod;
	}
}
void inv(i64 *o,i64 *a,i64 n)
{
	static i64 A[N],B[N];
	if(n==1){ o[0]=inv(a[0]); return ; }
	inv(o,a,(n+1)/2); init(n+n+4);
//	1/a-o=0, a=2a0-a0^2o
	fr(i,0,(1<<l)-1) A[i]=B[i]=0;
	fr(i,0,(n+1)/2-1) A[i]=o[i];
	fr(i,0,n-1) B[i]=a[i];
	NTT(A,1); NTT(B,1);
	fr(i,0,(1<<l)-1) A[i]=(2*A[i]-B[i]*A[i]%mod*A[i]%mod+mod)%mod;
	NTT(A,-1);
	fr(i,0,n-1) o[i]=A[i];
}
namespace C
{
	i64 f[N],F[N];
	void init(i64 n)
	{
		f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 C(i64 a,i64 b){ return a>=b&&b>=0?f[a]*F[b]%mod*F[a-b]%mod:0; }
}
int main()
{
	static i64 n,a[N],b[N],c[N],d[N],e[N],f[N];
	n=read()+1; C::init(N-1);
	fr(i,0,n-1) f[i]=a[i]=read();
	fr(i,0,n-1) b[i]=C::F[i+1];
	inv(c,b,n);
	fr(i,0,n-1) c[i]=c[i]*C::f[i]%mod;
	fr(i,0,n-1) d[n-i]=c[i]*C::F[i]%mod;
	fr(i,0,n-1) e[i]=a[i]*C::f[i]%mod;
	init(n+n); NTT(d,1); NTT(e,1);
	fr(i,0,(1<<l)-1) d[i]=d[i]*e[i]%mod;
	NTT(d,-1);
//	fr(j,1,n) fr(i,j-1,n-1) f[j]=(f[j]+e[i]%mod*d[i+1-j]%mod*C::F[j])%mod;
	fr(i,1,n) f[i]=(f[i]+d[n+i-1]*C::F[i])%mod;
	fr(i,0,n) printf("%lld%c",f[i],i==n?'\n':' ');
	return 0;
}
