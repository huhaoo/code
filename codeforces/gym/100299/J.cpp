/***************************************************************
	File name: J.cpp
	Author: huhao
	Create time: Mon 16 Nov 2020 08:48:24 PM CST
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
#include<vector>
#define poly std::vector<i64>
const int N=8200;
int n,mod;
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2); }
i64 p[N],f[N],a[N];
poly s[N];
poly operator*(poly a,poly b)
{
	poly c(a.size()+b.size()-1);
	fr(i,0,a.size()-1)
	{
		fr(j,0,b.size()-1) c[i+j]+=a[i]*b[j];
		if(i==end_i||i%8==0) fr(j,0,c.size()-1) c[j]%=mod;
	}
	return c;
}
poly operator%(poly a,poly b)
{
	int n=a.size()-1,m=b.size()-1;
//	for(auto i:b) printf("%lld ",i);; putchar(10);
	i64 I=inv(b[m]);
	fr(i,0,m) b[i]=b[i]*I%mod;
//	for(auto i:b) printf("%lld ",i);; putchar(10);
//	putchar(10);
	fd(i,n,m)
	{
		i64 k=a[i];
		int j=0;
		for(;j+3<=m;j+=4)
		{
			a[i-j]=(a[i-j]-k*b[m-j])%mod;
			a[i-j-1]=(a[i-j-1]-k*b[m-j-1])%mod;
			a[i-j-2]=(a[i-j-2]-k*b[m-j-2])%mod;
			a[i-j-3]=(a[i-j-3]-k*b[m-j-3])%mod;
		}
		for(;j<=m;j++) a[i-j]=(a[i-j]-k*b[m-j])%mod;
	}
	fr(i,0,m-1) a[i]=(a[i]%mod+mod)%mod;
	a.resize(m); return a;
}
void build(int k,int l,int r)
{
	if(l==r){ s[k]={1,mod-f[l]}; return ; }
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	s[k]=s[k<<1]*s[k<<1|1];
}
void solve(poly p,poly d,int k,int l,int r)
{
	if(l==r){ a[l]=p[0]*inv(d[0])%mod; return ; }
	int mid=(l+r)>>1;
	solve(p%s[k<<1],d*s[k<<1|1]%s[k<<1],k<<1,l,mid); solve(p%s[k<<1|1],d*s[k<<1]%s[k<<1|1],k<<1|1,mid+1,r);
}
int main()
{
	fr(T,1,read())
	{
		n=read(); mod=read(); int q=n;
		fr(i,1,n) p[i]=read();
		f[1]=1; f[2]=2;
		fr(i,3,n) f[i]=(f[i-1]+f[i-2])%mod;
		if(f[n]==0) n--;
		build(1,1,n);
		poly P;
		fr(i,1,n) P.push_back(p[i]);
		P=P*s[1]; P.resize(n);
//		for(auto i:P) printf("%lld ",i);; putchar(10);
		solve(P,{1},1,1,n);
		i64 ans=0;
		fr(i,1,n) ans=(ans+a[i]*power(f[i],q))%mod;
//		fr(i,1,n) printf("%lld%c",a[i],i==n?'\n':' ');
		printf("%lld\n",ans);
	}
	return 0;
}
