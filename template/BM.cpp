/***************************************************************
	File name: BM.cpp
	Author: huhao
	Create time: Fri 19 Jun 2020 02:13:52 PM CST
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
const int N=1<<18|10,mod=998244353;
const int g=3;
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2,mod); }
inline i64 Mod(i64 a){ return a>=mod?a-mod:a; }
#include<vector>
#define poly std::vector<i64>
namespace NTT
{
	i64 l,r[N],w[N];
	void init(int n)
	{
		l=1;
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
			i64 x=a[j+k],y=a[j+k+(1<<i)]*w[opt==1?(k<<(l-i-1)):(1<<l)-(k<<(l-i-1))]%mod;
			a[j+k]=Mod(x+y); a[j+k+(1<<i)]=Mod(x-y+mod);
		}
		if(opt==-1)
		{
			i64 I=inv(1<<l);
			fr(i,0,(1<<l)-1) a[i]=a[i]*I%mod;
		}
	}
	void mul(poly &c,poly a,poly b)
	{
		int n=a.size()-1,m=b.size()-1; init(n+m+1);
//		putchar(10);
//		fr(i,0,n) printf("%lld%c",a[i],i==n?'\n':' ');
//		fr(i,0,m) printf("%lld%c",b[i],i==m?'\n':' ');
		static i64 A[N],B[N];
		fr(i,0,(1<<l)-1) A[i]=B[i]=0;
		fr(i,0,n) A[i]=a[i];
		fr(i,0,m) B[i]=b[i];
		NTT(A,1); NTT(B,1);
		fr(i,0,(1<<l)-1) A[i]=A[i]*B[i]%mod;
		NTT(A,-1); c.resize(n+m+1);
		fr(i,0,n+m) c[i]=A[i];
//		fr(i,0,n+m) printf("%lld%c",c[i],i==n+m?'\n':' ');
	}
}
poly operator*(poly a,poly b){ NTT::mul(a,a,b); return a; }
poly operator+(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]=Mod(a[i]+b[i]); return a; }
poly operator-(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]=Mod(a[i]+mod-b[i]); return a; }
poly res(poly a,int n){ a.resize(n); return a; }
poly inv(poly a)
{
	int n=a.size(); //printf("%d\n",n);
	if(n==1) return poly(1,inv(a[0]));
	poly r=inv(res(a,(n+1)/2));
	return r+r-res(r*r*a,n);
}
poly operator/(poly a,poly b)
{
	int n=a.size(),m=b.size(); using std::reverse;
	reverse(a.begin(),a.end()); reverse(b.begin(),b.end());
	a=res(a*inv(res(b,n)),n-m+1);
	reverse(a.begin(),a.end());
	return a;
}
poly operator%(poly a,poly b)
{
//	putchar(10);
//	fr(i,0,a.size()-1) printf("%lld%c",a[i],i==end_i?'\n':' ');
//	fr(i,0,b.size()-1) printf("%lld%c",b[i],i==end_i?'\n':' ');
	if(a.size()<b.size()) return a;
//	fr(i,0,a.size()-b.size()) printf("%lld%c",(a/b)[i],i==end_i?'\n':' ');
//	fr(i,0,a.size()-1) printf("%lld%c",((a/b)*b)[i],i==end_i?'\n':' ');
	return res(a-b*(a/b),b.size()-1);
}
namespace BM
{
	i64 a[N],lst,m,A[N],l,d[N];
	void solve(i64 *f,int n)
	{
		m=l=lst=0; memset(a,0,sizeof(a)); memset(A,0,sizeof(A)); memset(d,0,sizeof(d));
		fr(i,0,n-1)
		{
			d[i]=f[i];
			fr(j,0,m-1) d[i]=Mod(d[i]-f[i-j-1]*a[j]%mod+mod);
//			printf("%d  %lld\n",i,d[i]);
			if(!d[i]) continue;
			if(!m){ m=i+1; lst=i; continue; }
			static i64 b[N]; i64 p=d[i]*inv(d[lst])%mod;
			fr(j,0,i-lst-2) b[j]=0;
			b[i-lst-1]=p;
			fr(j,0,l-1) b[i-lst+j]=p*(mod-A[j])%mod;
			fr(j,0,m-1) A[j]=a[j];
			fr(j,0,i-lst+l-1) a[j]=Mod(a[j]+b[j]);
			int k=l; l=m; m=i-lst+k; lst=i;
		}
	}
}
using BM::a; using BM::m;
i64 n,t,f[N];
int main()
{
	n=read(); t=read();
	fr(i,0,n-1) f[i]=read();
	BM::solve(f,n);
	fr(i,0,m-1) printf("%lld%c",a[i],i==m-1?'\n':' ');
	poly p(m+1); p[0]=1;
	fr(i,1,m) p[i]=mod-a[i-1];
	std::reverse(p.begin(),p.end());
	poly a(2),b(1); a[1]=b[0]=1;
	for(;t;t>>=1,a=a*a%p) if(t&1) b=b*a%p;
	i64 ans=0;
	fr(i,0,m-1) ans=(ans+b[i]*f[i])%mod;
	printf("%lld\n",ans);
	return 0;
}
