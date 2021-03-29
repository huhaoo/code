#include<stdio.h>
#include<algorithm>
#include<stdlib.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
const int N=1<<20|10,mod=998244353;
i64 inv(i64 a){ return power(a,mod-2,mod); }
const int g=3;
#include<vector>
#define poly std::vector<i64>
i64 I[N];
inline i64 Mod(i64 a){ return a>=mod?a-mod:a; }
namespace NTT
{
	i64 l,r[N],w[N];
	void init(int n)
	{
		l=0;
		while((1<<l)<n) l++;
		fr(i,0,(1<<l)-1) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		w[0]=1; w[1]=power(g,(mod-1)>>l,mod);
		fr(i,2,(1<<l)) w[i]=w[i-1]*w[1]%mod;
	}
	void NTT(i64 *a,int opt)
	{
		fr(i,0,(1<<l)-1) if(i<r[i]) std::swap(a[i],a[r[i]]);
		fr(i,0,l-1) for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
		{
			i64 x=a[j+k],y=a[j+k+(1<<i)]*w[opt==1?k<<(l-i-1):(1<<l)-(k<<(l-i-1))]%mod;
			a[j+k]=Mod(x+y); a[j+k+(1<<i)]=Mod(x-y+mod);
		}
		if(opt==-1) fr(i,0,(1<<l)-1) a[i]=a[i]*I[1<<l]%mod;
	}
	void mul(poly &c,poly a,poly b)
	{
		int n=a.size()-1,m=b.size()-1; static i64 A[N],B[N]; init(n+m+1);
		fr(i,0,(1<<l)-1) A[i]=B[i]=0;
		fr(i,0,n) A[i]=a[i];
		fr(i,0,m) B[i]=b[i];
		NTT(A,1); NTT(B,1);
		fr(i,0,(1<<l)-1) A[i]=A[i]*B[i]%mod;
		NTT(A,-1); c.resize(n+m+1);
		fr(i,0,n+m) c[i]=A[i];
	}
}
poly operator*(poly a,poly b){ poly c; NTT::mul(c,a,b); return c; }
poly operator+(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]=Mod(a[i]+b[i]); return a; }
poly operator-(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]=Mod(a[i]-b[i]+mod); return a; }
poly operator*(poly a,i64 b){ fr(i,0,a.size()-1) a[i]=a[i]*b%mod; return a; }
poly operator<<(poly a,i64 b){ a.resize(a.size()+b); fd(i,a.size()-1,b){ a[i]=a[i-b]; a[i-b]=0; } return a; }
poly operator>>(poly a,i64 b){ fr(i,0,a.size()-1-b) a[i]=a[i+b]; a.resize(a.size()-b); return a; }
poly res(poly a,int n){ a.resize(n); return a; }
poly inv(poly a)
{
	int n=a.size();
	if(n==1) return poly(1,inv(a[0]));
	poly r=inv(res(a,(n+1)/2));
	return r+r-res(r*r*a,n);
}
poly dx(poly a)
{
	fr(i,0,a.size()-2) a[i]=a[i+1]*(i+1)%mod;
	return res(a,a.size()-1);
}
poly integrate(poly a)
{
	a.resize(a.size()+1);
	fd(i,a.size()-1,1) a[i]=a[i-1]*I[i]%mod;
	a[0]=0; return a;
}
poly ln(poly a){ return res(integrate(dx(a)*inv(a)),a.size()); }
poly exp(poly a)
{
	int n=a.size();
	if(n==1) return poly(1,1);
	poly r=exp(res(a,(n+1)/2));
	return r-res(r*(ln(res(r,n))-a),n);
}
int n;
poly a[N];
struct Choose
{
	i64 f[N],F[N];
	Choose(int n)
	{
		f[0]=1; fr(i,1,n) f[i]=f[i-1]*i%mod;
		F[n]=inv(f[n]); fd(i,n,1) F[i-1]=F[i]*i%mod;
	}
	i64 operator()(i64 a,i64 b){ return a>=b&&b>=0?f[a]*F[b]%mod*F[a-b]%mod:0; }
} C(N-10);
poly OGF(poly a){ fr(i,0,a.size()-1) a[i]=a[i]*C.f[i]%mod; return a; }
poly EGF(poly a){ fr(i,0,a.size()-1) a[i]=a[i]*C.F[i]%mod; return a; }
poly solve(int l,int r)
{
	if(l>r) return poly(1,1);
	if(l==r) return a[l];
	int mid=(l+r)>>1;
	return solve(l,mid)*solve(mid+1,r);
}
void print(poly a)
{
	fr(i,0,a.size()-1) printf("%lld%c",a[i],i==end_i?'\n':' ');
}
int main()
{
	fr(i,1,N-10) I[i]=inv(i);
	n=read(); i64 s=0;
	fr(t,1,n)
	{
		i64 m=read(); s+=m;
		poly g(m+1),f(m+1);
//		printf("\n%lld\n",m);
		fr(i,1,m) f[i]=C(m+i-1,2*i-1);
		fr(i,1,m) f[i]=f[i]*(i&1?mod-1:1)%mod*C.f[i-1]%mod;
		if(t==n) fr(i,1,m) f[i]=f[i]*I[i]%mod;
		fr(i,0,m) g[m-i]=C.F[i];
//		print(f);
//		print(g);
		f=f*g; a[t].resize(m+1);
		fr(i,1,m) a[t][i]=f[i+m]*C.F[i-1]%mod*C.F[i]%mod*(i&1?mod-1:1)%mod;
//		print(a[t]);
	}
	poly T;
//	print(OGF(a[n]));
//	print(EGF(OGF(a[n])>>1));
	T=EGF(OGF(a[n])>>1)*solve(1,n-1);
//	print(T);
	T=T-EGF(OGF(a[n])>>2)*solve(1,n-1);
	i64 ans=0;
//	fr(j,1,n) fr(i,0,a[j].size()-1) printf("%lld%c",OGF(a[j])[i],i==end_i?'\n':' ');
//	print(T);
	fr(i,0,T.size()-1) ans=(ans+T[i]*C.f[i]%mod*s)%mod;
	printf("%lld\n",ans);
	return 0;
}
