/***************************************************************
	File name: 5293.cpp 
	Author: huhao
	Create time: Fri 19 Apr 2019 12:30:05 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(long long i=(a),end_##i=(b);i>=end_##i;i--)
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
const int N=65536<<3;
long long n,k,m,x,y,p,g,wk,pwk,c[N],r[N],l;
long long power(long long a,long long b,long long p)
{
	long long r=1;
	if(b<0)
		exit(-1);
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
void init(long long p)
{
	if(p<=3)
	{
		g=p-1;
		wk=power(g,(p-1)/k,p);
		pwk=power(wk,p-2,p);
		return;
	}
	long long x=p-1;
	for(long long i=2;i*i<=x;i++)
		if(x%i==0)
		{
			c[++c[0]]=i;
			while(x%i==0)
				x/=i;
		}
	if(x!=1)
		c[++c[0]]=x;
	g=2;
	while(1)
	{
		int flag=1;
		fr(i,1,c[0])
			if(power(g,(p-1)/c[i],p)==1)
			{
				flag=0;
				break;
			}
		if(flag)
			break;
		g++;
	}
	wk=power(g,(p-1)/k,p);
	pwk=power(wk,p-2,p);
}
struct comp
{
	long double real,imag;
	inline comp(long double _r=0.,long double _i=0.)
	{
		real=_r;
		imag=_i;
	}
	inline void clear()
	{
		real=imag=0;
	}
	inline comp operator+(comp a)
	{
		return comp(real+a.real,imag+a.imag);
	}
	inline comp& operator+=(comp a)
	{
		return *this=*this+a;
	}
	inline comp operator-(comp a)
	{
		return comp(real-a.real,imag-a.imag);
	}
	inline comp& operator-=(comp a)
	{
		return *this=*this-a;
	}
	inline comp operator*(comp a)
	{
		return comp(real*a.real-imag*a.imag,real*a.imag+imag*a.real);
	}
	inline comp operator*=(comp a)
	{
		return *this=*this*a;
	}
	inline comp& operator*=(long double a)
	{
		real*=a;
		imag*=a;
		return *this;
	}
	inline comp& operator/=(long double a)
	{
		real/=a;
		imag/=a;
		return *this;
	}
	inline comp operator*(long double a)
	{
		comp x=*this;
		return x*=a;
	}
	inline comp operator/(long double a)
	{
		comp x=*this;
		return x/=a;
	}
};
const int M=5;
struct matrix
{
	int n,m;
	long long a[M][M];
	void clear()
	{
		n=m=0;
		memset(a,0,sizeof(a));
	}
	matrix()
	{
		clear();
	}
	matrix& operator+=(matrix x)
	{
		fr(i,1,n)
			fr(j,1,m)
				a[i][j]+=x.a[i][j];
		return *this;
	}
	matrix operator+(matrix x)
	{
		matrix y=*this;
		return y+=x;
	}
	matrix operator*(matrix x)
	{
		matrix y;
		y.n=n;
		y.m=x.m;
		fr(i,1,y.n)
			fr(j,1,y.m)
				fr(k,1,m)
					y.a[i][j]=(y.a[i][j]+a[i][k]*x.a[k][j])%p;
		return y;
	}
	matrix& operator*=(matrix x)
	{
		return *this=*this*x;
	}
	matrix operator*(long long x)
	{
		matrix y=*this;
		fr(i,1,n)
			fr(j,1,m)
				y.a[i][j]=y.a[i][j]*x%p;
		return y;
	}
	matrix& operator*=(long long x)
	{
		return *this=*this*x;
	}
};
matrix operator*(long long x,matrix y)
{
	return y*x;
}
matrix E(int x)
{
	matrix e;
	e.n=e.m=x;
	fr(i,1,x)
		e.a[i][i]=1;
	return e;
}
matrix operator^(matrix _a,long long b)
{
	matrix r=E(_a.n),a=_a;
	while(b)
	{
		if(b&1)
			r*=a;
		a*=a;
		b>>=1;
	}
	return r;
}
matrix& operator^=(matrix& _a,long long b)
{
	return _a=_a^b;
}
const long double pi=std::acos(-1.);
void FFT(comp *a,int opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		comp wn=comp(std::cos(pi/(1<<i)),opt*std::sin(pi/(1<<i)));
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			comp w=comp(1,0);
			fr(k,0,(1<<i)-1)
			{
				comp x=a[j+k],y=w*a[(1<<i)+j+k];
				a[j+k]=x+y;
				a[(1<<i)+j+k]=x-y;
				w*=wn;
			}
		}
	}
	if(opt==-1)
	{
		fr(i,0,(1<<l)-1)
			a[i]/=(long double)(1<<l);
	}
}
comp a1[N],a2[N],b1[N],b2[N],c1[N],c2[N],c3[N],c4[N];
void MTT(long long *c,long long *a,long long *b,long long n,long long m)
{
	l=0;
	while((1<<l)<(n+m+1))
		l++;
	fr(i,0,(1<<l)-1)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,0,(1<<l)-1)
		a1[i]=a2[i]=b1[i]=b2[i]=comp(0,0);
	fr(i,0,n)
	{
		a1[i]=a[i]/(1<<15);
		a2[i]=a[i]%(1<<15);
	}
	fr(i,0,m)
	{
		b1[i]=b[i]/(1<<15);
		b2[i]=b[i]%(1<<15);
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
		c[i]=((long long)(c1[i].real+0.5)%p*(1ll<<30)%p+(long long)(c2[i].real+0.5)%p*(1ll<<15)%p+(long long)(c3[i].real+0.5)%p*(1ll<<15)%p+(long long)(c4[i].real+0.5))%p;
}
long long a[N],b[N],ab[N];
matrix _a,_b;
int main()
{
	m=read();
	k=read();
	n=read();
	x=read();
	y=read();
	p=read();
	init(p);
//	printf("%lld %lld %lld %lld\n",p,g,wk,pwk);
	_a.n=_a.m=m;
	fr(j,1,m)
		fr(i,1,m)
			_a.a[i][j]=read();
	_b.n=m;
	_b.m=1;
	fr(i,1,m)
		_b.a[i][1]=(i==x);
	fr(i,0,k-1)
		a[i]=power(wk,i*(i-1)/2,p)*(((E(m)+_a*power(wk,i,p))^n)*_b).a[y][1]%p;
	fr(i,0,2*k)
		b[i]=power(pwk,(2*k-i)*(2*k-i-1)/2,p);
	MTT(ab,a,b,k-1,2*k);
	long long ik=power(k,p-2,p);
	fr(i,0,k-1)
		printf("%lld\n",ik*power(wk,i*(i-1)/2,p)%p*ab[2*k-i]%p);
	return 0;
}
