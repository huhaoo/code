/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Fri 30 Oct 2020 05:20:52 PM CST
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
poly operator+(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]+=b[i]; return a; }
poly operator-(poly a,poly b){ a.resize(std::max(a.size(),b.size())); fr(i,0,b.size()-1) a[i]-=b[i]; return a; }
poly operator<<(poly a,int b){ a.resize(a.size()+b); fd(i,a.size()-1,b) a[i]=a[i-b]; fr(i,0,b-1) a[i]=0; return a; }
#define f80 double
#define i64 long long
#include<complex>
//#define comp std::complex<f80>
struct comp
{
	f80 x,y;
	f80 real(){ return x; }
	f80 imag(){ return y; }
	void real(f80 X){ x=X; }
	void imag(f80 Y){ y=Y; }
	comp(){ x=0; y=0; }
	comp(f80 X){ x=X; y=0; }
	comp(f80 X,f80 Y){ x=X; y=Y; }
} ;
comp operator/(comp a,f80 b){ return comp(a.x/b,a.y/b); }
comp &operator/=(comp &a,f80 b){ return a=a/b; }
comp operator+(comp a,comp b){ return comp(a.x+b.x,a.y+b.y); }
comp operator-(comp a,comp b){ return comp(a.x-b.x,a.y-b.y); }
comp operator*(comp a,comp b){ return comp(a.x*b.x-a.y*b.y,a.x*b.y+b.x*a.y); }
comp conj(comp a){ return comp(a.x,-a.y); }
comp inv(comp a){ return conj(a)/(a.x*a.x+a.y*a.y); }
comp operator/(comp a,comp b){ return a*inv(b); }
const int N=1<<19|10,P=31622;
const f80 pi=std::acos(-1.);
namespace fft
{
	i64 l,r[N];
	comp w[N];
	void init(int n)
	{
		l=1; while((1<<l)<n) l++;
		fr(i,0,(1<<l)-1) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
//		w[0]=comp(1,0); w[1]=comp(cos(pi*2/(1<<l)),sin(pi*2/(1<<l)));
//		fr(i,2,(1<<l)) w[i]=w[i-1]*w[1];
		fr(i,0,(1<<l)) w[i]=comp(std::cos(i*pi*2/(1<<l)),std::sin(i*pi*2/(1<<l)));
//		fprintf(stderr,"%.20Lf %.20Lf\n",w[1<<l].real(),w[1<<l].imag());
	}
	void fft(comp *a,int opt)
	{
		fr(i,0,(1<<l)-1) if(i<r[i]) std::swap(a[i],a[r[i]]);
		fr(i,0,l-1) for(int j=0;j<(1<<l);j+=(1<<(i+1))) fr(k,0,(1<<i)-1)
		{
			comp x=a[j+k],y=w[opt==1?(k<<(l-i-1)):(1<<l)-(k<<(l-i-1))]*a[j+k+(1<<i)];
			a[j+k]=x+y; a[j+k+(1<<i)]=x-y;
		}
		if(opt==-1) fr(i,0,(1<<l)-1) a[i]/=(f80)(1<<l);
	}
	i64 Z(comp a){ return (i64)(a.real()+(a.real()<0?-0.5:0.5)); }
	void mergedft(comp *a,comp *b)
	{
//		fft(a,1); fft(b,1); return ;
		fr(i,0,(1<<l)-1) a[i].imag(b[i].real());
		fft(a,1); a[1<<l]=a[0];
		fr(i,0,(1<<l)-1) b[i]=conj(a[(1<<l)-i]);
		fr(i,0,(1<<l)-1)
		{
			comp A=a[i],B=b[i];
			a[i]=(A+B)/comp(2,0); b[i]=(A-B)/comp(0,2);
		}
	}
	void mergeidft(comp *a,comp *b)
	{
//		fft(a,-1); fft(b,-1); return ;
		fr(i,0,(1<<l)-1) a[i]=a[i]+b[i]*comp(0,1);
		fft(a,-1);
		fr(i,0,(1<<l)-1){ b[i]=a[i].imag(); a[i].imag(0); }
	}
	void mul(i64 *o,i64 *a,i64 *b,int n,int m,i64 p)
	{
		init(n+m+1); static comp a1[N],a2[N],b1[N],b2[N],c1[N],c2[N],c3[N];
		fr(i,0,(1<<l)-1) a1[i]=a2[i]=b1[i]=b2[i]=c1[i]=c2[i]=c3[i]=0;
		fr(i,0,n){ a2[i]=a[i]/P; a1[i]=a[i]%P; }
		fr(i,0,m){ b2[i]=b[i]/P; b1[i]=b[i]%P; }
		mergedft(a1,a2); mergedft(b1,b2);
		fr(i,0,(1<<l)-1){ c1[i]=a1[i]*b1[i]; c2[i]=a1[i]*b2[i]+a2[i]*b1[i]; c3[i]=a2[i]*b2[i]; }
		mergeidft(c1,c2); fft(c3,-1);
		fr(i,0,n+m){ o[i]=((Z(c3[i])%p*P*P)+(Z(c2[i])%p*P)+Z(c1[i]))%p; }
	}
}
const int mod=1000003;
poly operator*(poly a,poly b)
{
	static i64 A[N],B[N];
	fr(i,0,a.size()-1) A[i]=a[i];
	fr(i,0,b.size()-1) B[i]=b[i];
	fft::mul(A,A,B,a.size()-1,b.size()-1,mod);
	a.resize(a.size()+b.size()-1);
	fr(i,0,a.size()-1) a[i]=A[i];
	return a;
}
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2); }
i64 f[N],F[N],n,a,b,c,x[N],y[N],ans;
i64 C(i64 a,i64 b){ return f[a]*F[b]%mod*F[a-b]%mod; }
i64 Q(i64 x,i64 y){ return C(x+y,x)*power(a,x)%mod*power(b,y)%mod; }
int main()
{
	f[0]=1; fr(i,1,N-5) f[i]=f[i-1]*i%mod;
	F[N-5]=inv(f[N-5]); fd(i,N-5,1) F[i-1]=F[i]*i%mod;
	n=read(); a=read(); b=read(); c=read();
	fr(i,1,n) y[i]=read();
	fr(i,1,n) x[i]=read();
	fr(i,2,n) ans+=Q(n-i,n-2)*x[i]*b%mod;
	fr(i,2,n) ans+=Q(n-2,n-i)*y[i]*a%mod;
	poly A(n-1),B(n-1);
	fr(i,0,n-2){ A[i]=F[i]*power(a,i)%mod; B[i]=F[i]*power(b,i)%mod; }
	A=A*B;
	fr(i,0,A.size()-1) ans+=A[i]%mod*f[i]%mod*c%mod;
	printf("%lld\n",ans%mod);
	return 0;
}
