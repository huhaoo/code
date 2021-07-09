#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const int N=4000010,mod=998244353;
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2); }
struct Math
{
	i64 f[N],F[N];
	Math(int n)
	{
		f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=::inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 inv(i64 a){ return a>0?f[a-1]*F[a]%mod:0; }
	i64 operator()(i64 a,i64 b){ return f[a]*F[b]%mod*F[a-b]%mod; }
} C(N-10);
i64 Q(i64 a,i64 b,i64 c)
{
	return a>=0&&b>=0&&c>=0?C(a+b,b)*C(b+c,b)%mod:0;
}
int main()
{
/*	i64 a=read(),b=read(),c=read(),ans=0;
	fr(k,0,std::min(a,c))
		ans=(ans+C.f[a+b+c-k]*C.F[a-k]%mod*C.F[b]%mod*C.F[c-k]%mod*C.F[k]%mod*(k&1?-1:1))%mod;
	printf("%I64d %I64d\n",(ans%mod+mod)*C.f[a]%mod*C.f[b]%mod*C.f[c]%mod,
	                       C.f[a+b]*C.f[b+c]%mod*C.F[b]%mod);*/
	fr(T,1,read())
	{
		int n=read(),x=read();
		i64 ans=C.f[n-1];
		ans-=(x==1?0:C.f[n-1]*C.inv(n+1-x)%mod);
		ans-=(x==n?0:C.f[n-1]*C.inv(x)%mod);
		ans+=(x<=2?0:C.f[n-1]*C.inv(n+1-x)%mod*C.inv(n+2-x)%mod);
		ans+=(x>=n-1?0:C.f[n-1]*C.inv(x)%mod*C.inv(x+1)%mod);
		ans+=(x==1||x==n?0:C.f[n-2])*2;
		ans-=(x<=2||x==n?0:C.f[n-2]*C.inv(n+1-x)%mod);
		ans-=(x==1||x>=n-1?0:C.f[n-2]*C.inv(x)%mod);
/*		fr(y,1,x-1)
		{
			i64 a=y-1,b=x-y-1,c=n-x;
//			ans=(ans-a*c%mod*Q(a-1,b,c-1)%mod)%mod;
		}
		fr(y,x+1,n)
		{
			i64 a=x-1,b=y-x-1,c=n-y;
//			ans=(ans-a*c%mod*Q(a-1,b,c-1)%mod)%mod;
		}*/
		printf("%d\n",(int)((ans%mod+mod)%mod));
	}
	return 0;
}