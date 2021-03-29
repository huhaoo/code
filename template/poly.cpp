/***************************************************************
	File name: poly.cpp
	Author: huhao
	Create time: Fri 14 Aug 2020 02:38:22 PM CST
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
#define i64 long long
const int N=1<<20|10,mod=998244353;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1; a%=p;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2,mod); }
inline i64 Mod(i64 a){ return a>=mod?a-mod:a; }
inline void Add(i64 &a,i64 b){ a=Mod(a+b); }
const int g=3;
#include<vector>
#define poly std::vector<i64>
i64 I[N];
namespace NTT
{
	int r[N],l;
	i64 w[N];
	void init(int n)
	{
		l=0;
		while((1<<l)<n) l++;
		fr(i,0,(1<<l)-1) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		w[0]=1; w[1]=power(g,(mod-1)>>l,mod);
		fr(i,2,1<<l) w[i]=w[i-1]*w[1]%mod;
	}
	void NTT(i64 *a,int opt)
	{
		fr(i,0,(1<<l)-1) if(i<r[i]) std::swap(a[i],a[r[i]]);
		fr(i,0,l-1) for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
		{
			i64 x=a[j+k],y=a[j+k+(1<<i)]*w[opt==1?(k<<(l-i-1)):(1<<l)-(k<<(l-i-1))]%mod;
			a[j+k]=Mod(x+y); a[j+k+(1<<i)]=Mod(x-y+mod);
		}
		if(opt==-1) fr(i,0,(1<<l)-1) a[i]=a[i]*I[1<<l]%mod;
	}
	void mul(poly &c,poly a,poly b)
	{
		int n=a.size()-1,m=b.size()-1;
		init(n+m+1); static i64 A[N],B[N];
		fr(i,0,(1<<l)-1) A[i]=B[i]=0;
		fr(i,0,n) A[i]=a[i];
		fr(i,0,m) B[i]=b[i];
		NTT(A,1); NTT(B,1);
		fr(i,0,(1<<l)-1) A[i]=A[i]*B[i]%mod;
		NTT(A,-1); c.resize(n+m+1);
		fr(i,0,n+m) c[i]=A[i];
	}
}
poly operator+(poly a,poly b)
{
	if(a.size()<b.size()) a.resize(b.size());
	fr(i,0,b.size()-1) Add(a[i],b[i]);
	return a;
}
poly operator-(poly a,poly b)
{
	if(a.size()<b.size()) a.resize(b.size());
	fr(i,0,b.size()-1) Add(a[i],mod-b[i]);
	return a;
}
poly operator*(poly a,int b)
{
	fr(i,0,a.size()-1) a[i]=a[i]*b%mod;
	return a;
}
poly operator*(poly a,poly b){ NTT::mul(a,a,b); return a; }
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
poly ln(poly a){ return integrate(res(dx(a)*inv(a),a.size()-1)); }
poly exp(poly a)
{
	int n=a.size();
	if(n==1) return poly(1,1);
	poly r=exp(res(a,(n+1)/2));
	return r-res(r*(ln(res(r,n))-a),n);
}int main()
{
	return 0;
}
