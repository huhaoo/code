/***************************************************************
	File name: MTT.cpp
	Author: huhao
	Create time: Thu 30 Jul 2020 07:28:03 PM CST
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
const int N=1<<20|10,P=31622;
const f80 pi=std::acos(-1.);
i64 n,m,p;
i64 a[N],b[N],c[N];
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
int main()
{
	n=read(); m=read(); p=read();
	fr(i,0,n)
	{
		a[i]=read()%p;
		if(a[i]>p/2) a[i]-=p;
	}
	fr(i,0,m)
	{
		b[i]=read()%p;
		if(b[i]>p/2) b[i]-=p;
	}
	fft::mul(c,a,b,n,m,p);
	fr(i,0,n+m) printf("%lld%c",(c[i]%p+p)%p,i==n+m?'\n':' ');
	return 0;
}
