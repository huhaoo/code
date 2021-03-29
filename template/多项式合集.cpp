/**************************************************************
	File name: 多项式合集.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 3/15/2019, 11:47:47 AM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(long long i=(a),end_##i=(b);i>=end_##i;i--)
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
long long readmod(long long p)
{
	long long r=0,t=1,c=getchar();
	while(c<'0'||c>'9')
	{
		t=c=='-'?-1:1;
		c=getchar();
	}
	while(c>='0'&&c<='9')
	{
		r=(r*10+c-48)%p;
		c=getchar();
	}
	return (r*t+p)%p;
}
const int N=(1<<18)+10;
namespace fft 
{
	long long p[N],l;
	struct comp
	{
		long double a,b;//a+bi
		comp(long double _a=0.,long double _b=0.)
		{
			a=_a;
			b=_b;
		}
		comp operator+(comp x)
		{
			x.a+=a;
			x.b+=b;
			return x;
		}
		comp operator-(comp x)
		{
			x.a=a-x.a;
			x.b=b-x.b;
			return x;
		}
		comp operator*(comp x)
		{
			comp r;
			r.a=a*x.a-b*x.b;
			r.b=a*x.b+b*x.a;
			return r;
		}
		comp operator*=(comp x)
		{
			return *this=*this*x;
		}
	};
	comp _a[N],_b[N],_c[N];
	void init(long long n)
	{
		l=0;
		while((1<<l)<n)
			l++;
		fr(i,0,(1<<l)-1)
			p[i]=(p[i>>1]>>1)|((i&1)<<(l-1));
	}
	void FFT(comp *a,long long opt)
	{
		long double pi=acos(-1.);
		fr(i,0,(1<<l)-1)
			if(i<p[i])
				swap(a[i],a[p[i]]);
		fr(i,0,l-1)
		{
			comp wn=comp(std::cos(pi/(1<<i)),opt*std::sin(pi/(1<<i)));
			for(long long j=0;j<(1<<l);j+=(1<<(i+1)))
			{
				comp w=comp(1,0);
				fr(k,0,(1<<i)-1)
				{
					comp x=a[j+k],y=w*a[j+k+(1<<i)];
					a[j+k]=x+y;
					a[j+k+(1<<i)]=x-y;
					w*=wn;
				}
			}
		}
		if(opt==-1)
		{
			fr(i,0,(1<<l)-1)
			{
				a[i].a/=(1<<l)*1.;
				a[i].b/=(1<<l)*1.;
			}
		}
	}
	void mul(long long *c,long long *a,long long *b,long long n,long long m)
	{
		init(n+m+1);
		fr(i,0,(1<<l)-1)
			_a[i]=_b[i]=comp(0,0);
		fr(i,0,n)
			_a[i].a=a[i]*1.;
		fr(i,0,m)
			_b[i].a=b[i]*1.;
		FFT(_a,1);
		FFT(_b,1);
		fr(i,0,(1<<l)-1)
			_c[i]=_a[i]*_b[i];
		FFT(_c,-1);
		fr(i,0,n+m)
			c[i]=(long long)(_c[i].a+0.5);
	}
	comp a1[N],a2[N],b1[N],b2[N],c1[N],c2[N],c3[N],c4[N];
	void MTT(long long *c,long long *a,long long *b,long long n,long long m,long long p)
	{
		init(n+m+1);
		fr(i,0,(1<<l)-1)
			a1[i]=b1[i]=a2[i]=b2[i]=comp(0,0);
		fr(i,0,n)
		{
			a1[i].a=a[i]/(1<<15);
			a2[i].a=a[i]%(1<<15);
		}
		fr(i,0,m)
		{
			b1[i].a=b[i]/(1<<15);
			b2[i].a=b[i]%(1<<15);
		}
		FFT(a1,1);
		FFT(a2,1);
		FFT(b1,1);
		FFT(b2,1);
		fr(i,0,(1<<l)-1)
		{
			c1[i]=a1[i]*b1[i];
			c2[i]=a1[i]*b2[i];
			c3[i]=a2[i]*b1[i];
			c4[i]=a2[i]*b2[i];
		}
		FFT(c1,-1);
		FFT(c2,-1);
		FFT(c3,-1);
		FFT(c4,-1);
		fr(i,0,n+m)
			c[i]=(((long long)(c1[i].a+0.5)%p*(1ll<<30ll)%p)+((long long)(c2[i].a+0.5)%p*(1ll<<15ll)%p)+((long long)(c3[i].a+0.5)%p*(1ll<<15ll)%p)+((long long)(c4[i].a+0.5)%p))%p;
	}
	long long power(long long a,long long b,long long p)
	{
		long long r=1;
		while(b)
		{
			if(b&1)
				r=r*a%p;
			a=a*a%p;
			b>>=1;
		}
		return r;
	}
	long long _d[N];
	void inv(long long *c,long long *a,long long n,long long p)
	{
		if(n==1)
		{
			*c=power(*a,p-2,p);
			return;
		}
		inv(c,a,(n+1)/2,p);
		MTT(_d,a,c,n-1,n-1,p);
		fr(i,n,2*n-2)
			_d[i]=0;
		fr(i,1,n-1)
			_d[i]=p-_d[i];
		_d[0]=(p-_d[0]+2)%p;
		MTT(c,_d,c,n-1,n-1,p);
		fr(i,n,2*n-2)
			c[i]=0;
	}
	/*
		f(g(x))=1/g(x)-h(x)
		g(x)=g0(x)(2-h(x)g0(x))
	*/
}
#include<stdlib.h>
namespace ntt
{
	const long long mod=998244353,g=3,gi=332748118;
	long long l,p[N];
	long long _a[N],_b[N],_c[N];
	long long power(long long a,long long b,long long m)
	{
		long long r=1;
		a%=m;
		while(b)
		{
			if(b&1)
				r=r*a%m;
			a=a*a%m;
			b>>=1;
		}
		return r;
	}
	long long inv(long long a)
	{
		return power(a,mod-2,mod);
	}
	void init(long long n)
	{
		if((1<<l)>=n&&(1<<(l-1))<n)
			return;
		l=0;
		while((1<<l)<n)
			l++;
		fr(i,0,(1<<l)-1)
			p[i]=(p[i>>1]>>1)|((i&1)<<(l-1));
	}
	void NTT(long long *a,long long opt)
	{
		fr(i,0,(1<<l)-1)
			if(i<p[i])
				swap(a[i],a[p[i]]);
		fr(i,0,l-1)
		{
			long long wn=power(opt==1?g:gi,(mod-1)/(1<<(i+1)),mod);
			for(long long j=0;j<(1<<l);j+=(1<<(i+1)))
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
			long long i=inv(1<<l);
			fr(j,0,(1<<l)-1)
				a[j]=a[j]*i%mod;
		}
	}
	void mul(long long *c,long long *a,long long *b,long long n,long long m)
	{
		init(n+m+1);
		fr(i,0,(1<<l)-1)
			_a[i]=_b[i]=0;
		fr(i,0,n)
			_a[i]=a[i];
		fr(i,0,m)
			_b[i]=b[i];
		NTT(_a,1);
		NTT(_b,1);
		fr(i,0,(1<<l)-1)
			_c[i]=_a[i]*_b[i]%mod;
		NTT(_c,-1);
		fr(i,0,n+m)
			c[i]=_c[i];
	}
	long long _d[N];
	void inv(long long *c,long long *a,long long p)
	{
		if(p==1)
		{
			c[0]=inv(a[0]);
			return;
		}
		inv(c,a,(p+1)/2);
		mul(_d,a,c,p-1,p-1);
		fr(i,p,p+p-2)
			_d[i]=0;
		fr(i,1,p-1)
			_d[i]=mod-_d[i];
		_d[0]=(2+mod-_d[0])%mod;
		mul(c,_d,c,p-1,p-1);
		fr(i,p,p+p-2)
			c[i]=0;
	}
	struct simcomp
	{
		long long a,b,x;//a+b sqrt(x)
		simcomp(long long _a=0,long long _b=0,long long _x=0)
		{
			a=_a;
			b=_b;
			x=_x;
		}
		simcomp operator*(simcomp c)
		{
			return x==c.x?simcomp((a*c.a+b*c.b%mod*x)%mod,(a*c.b+b*c.a)%mod,x):-1;
		}
		simcomp operator*=(simcomp c)
		{
			return *this=*this*c;
		}
	};
	long long sqrt_mod(long long k)
	{
		if(k==0)
			return 0;
		srand((unsigned long long)new char);
		if(power(k,(mod-1)/2,mod)!=1)
			return -1;
		long long a=rand()%mod;
		while(power(a*a-k+mod,(mod-1)/2,mod)==1)
			a=rand()%mod;
		simcomp x=simcomp(a,1,(a*a-k+mod)%mod),y;
		y=x;
		long long p=(mod-1)/2;
		while(p)
		{
			if(p&1)
				y*=x;
			x*=x;
			p>>=1;
		}
		return y.a;
	}
	long long _e[N];
	void sqrt(long long *c,long long *a,long long p)
	{
		if(p==1)
		{
			c[0]=sqrt_mod(a[0]);
			if(c[0]==-1)
				exit(-1);
			if(c[0]>mod-c[0])
				c[0]=mod-c[0];
			return;
		}
		sqrt(c,a,(p+1)/2);
		fr(i,0,p-1)
			_e[i]=0;
		inv(_e,c,p);
		mul(_e,a,_e,p-1,p-1);
		fr(i,p,p+p-2)
			_e[i]=0;
		long long p2=inv(2);
		fr(i,0,p-1)
			c[i]=(c[i]+_e[i])*p2%mod;
	}
	void d(long long *c,long long *a,long long l)
	{
		fr(i,0,l-2)
			c[i]=a[i+1]*(i+1)%mod;
		c[l-1]=0;
	}
	void integral(long long *c,long long *a,long long l)
	{
		fr(i,1,l-1)
			c[i]=a[i-1]*inv(i)%mod;
		c[0]=0;
	}
	long long _f[N];
	void ln(long long *c,long long *a,long long l)
	{
		d(_f,a,l);
		inv(c,a,l);
		mul(_f,_f,c,l-1,l-1);
		fr(i,l,l+l-2)
			_f[i]=0;
		integral(c,_f,l);
	}
	long long _g[N];
	void exp(long long *c,long long *a,long long l)
	{
		if(l==1)
		{
			if(a[0]!=0)
				exit(-1);
			c[0]=1;
			return;
		}
		exp(c,a,(l+1)/2);
		ln(_g,c,l);
		fr(i,0,l-1)
			_g[i]=a[i]-_g[i];
		_g[0]++;
		mul(c,c,_g,l-1,l-1);
	}
	void reverse(long long *l,long long *r)
	{
		while(l<r)
		{
			swap(*l,*r);
			l++;
			r--;
		}
	}
	void divmod(long long *q,long long *r,long long *f,long long *g,long long n,long long m)
	{
		long long lq=n-m;
		reverse(f,f+n);
		reverse(g,g+m);
		inv(q,g,lq+1);
		mul(q,q,f,lq,lq);
		fr(i,lq+1,lq*2)
			q[i]=0;
		reverse(f,f+n);
		reverse(g,g+m);
		reverse(q,q+lq);
		mul(r,g,q,n,n);
		fr(i,n+1,n*2)
			r[i]=0;
		fr(i,0,n)
			r[i]=(f[i]-r[i]+mod)%mod;
	}
	long long _h[N],_i[N];
	void power(long long *c,long long *a,long long n,long long k)
	{
		if(!*a)
		{
			long long i=0;
			while(!a[i]&&i<n)
				i++;
			if(i==n||i*k>=n)
			{
				fr(j,0,n-1)
					c[j]=0;
				return;
			}
			power(_i,a+i,n-i,k);
			fr(j,k*i,n-1)
				c[j]=_i[j-k*i];
			fr(j,0,k*i-1)
				c[j]=0;
			return;
		}
		long long aa=*a,ai=inv(*a),ap=power(*a,k,mod);
		fr(i,0,n-1)
			a[i]=a[i]*ai%mod;
		ln(_h,a,n);
		fr(i,0,n-1)
			_h[i]=_h[i]*k%mod;
		exp(c,_h,n);
		fr(i,0,n-1)
		{
			a[i]=a[i]*aa%mod;
			c[i]=c[i]*ap%mod;
		}
	}
}
namespace fwt
{
	const int mod=998244353,i2=(mod+1)/2;
	void fwtor(long long *a,long long n,long long opt)
	{
		fr(i,0,n-1)
			for(int j=0;j<(1<<n);j+=(1<<(i+1)))
				fr(k,0,(1<<i)-1)
					a[j+k+(1<<i)]=(a[j+k+(1<<i)]+opt*a[j+k]+mod)%mod;
	}
	void fwtand(long long *a,long long n,long long opt)
	{
		fr(i,0,n-1)
			for(int j=0;j<(1<<n);j+=(1<<(i+1)))
				fr(k,0,(1<<i)-1)
					a[j+k]=(a[j+k]+opt*a[j+k+(1<<i)]+mod)%mod;
	}
	void fwtxor(long long *a,long long n,long long opt)
	{
		opt=(opt==1?1:i2);
		fr(i,0,n-1)
			for(int j=0;j<(1<<n);j+=(1<<(i+1)))
				fr(k,0,(1<<i)-1)
				{
					long long x=a[j+k],y=a[j+k+(1<<i)];
					a[j+k]=(x+y)*opt%mod;
					a[j+k+(1<<i)]=(x-y+mod)*opt%mod;
				}
	}
	const int or_tag=1,and_tag=2,xor_tag=3;
	long long _a[N],_b[N];
	void fwt(long long *c,long long *a,long long *b,long long n,long long opt)
	{
		fr(i,0,(1<<n)-1)
		{
			_a[i]=a[i];
			_b[i]=b[i];
		}
		if(opt==or_tag)
		{
			fwtor(a,n,1);
			fwtor(b,n,1);
			fr(i,0,(1<<n)-1)
				c[i]=a[i]*b[i]%mod;
			fwtor(c,n,-1);
		}
		else if(opt==and_tag)
		{

			fwtand(a,n,1);
			fwtand(b,n,1);
			fr(i,0,(1<<n)-1)
				c[i]=a[i]*b[i]%mod;
			fwtand(c,n,-1);
		}
		else if(opt==xor_tag)
		{
			fwtxor(a,n,1);
			fwtxor(b,n,1);
			fr(i,0,(1<<n)-1)
				c[i]=a[i]*b[i]%mod;
			fwtxor(c,n,-1);
		}
		fr(i,0,(1<<n)-1)
		{
			a[i]=_a[i];
			b[i]=_b[i];
		}
	}
}
int main()
{
	return 0;
}

