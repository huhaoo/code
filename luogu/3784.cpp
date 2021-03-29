/***************************************************************
	File name: 3784.cpp
	Author: huhao
	Create time: Sun 05 May 2019 02:50:34 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
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
#define N (1<<20)+10
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
	void d(long long *c,long long *a,long long l,long long p)
	{
		fr(i,0,l-2)
			c[i]=a[i+1]*(i+1)%p;
		c[l-1]=0;
	}
	void integral(long long *c,long long *a,long long l,long long p)
	{
		fr(i,1,l-1)
			c[i]=a[i-1]*power(i,p-2,p)%p;
		c[0]=0;
	}
	long long _f[N];
	void ln(long long *c,long long *a,long long l,long long p)
	{
		d(_f,a,l,p);
		inv(c,a,l,p);
		MTT(_f,_f,c,l-1,l-1,p);
		fr(i,l,l+l-2)
			_f[i]=0;
		integral(c,_f,l,p);
	}
}
long long n,a[N],b[N],p,s[N],ans[N];
int main()
{
	n=read();
	p=read();
	a[0]=1;
	fr(i,1,n)
		a[i]=read();
	fft::ln(b,a,n+1,p);
	fr(i,1,n)
		b[i]=b[i]*i%p;
	fr(i,1,n)
	{
		if(b[i]!=s[i])
		{
			ans[++ans[0]]=i;
			fr(j,1,n/i)
				s[i*j]=(s[i*j]+i)%p;
		}
	}
	printf("%lld\n",ans[0]);
	fr(i,1,ans[0])
		printf("%lld%c",ans[i],i==ans[0]?'\n':' ');
	return 0;
}

