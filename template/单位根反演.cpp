/***************************************************************
	File name: 单位根反演.cpp
	Author: huhao
	Create time: Thu 18 Apr 2019 12:37:31 PM CST
	Sample:
	- bzoj3328
	  https://www.lydsy.com/JudgeOnline/problem.php?id=3328
***************************************************************/
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
		r=r*10+c-48;
		c=getchar();
	}
	return r*t;
}
const int N=5;
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
long long p,g,wk,n,k,c[N];
struct matrix
{
	long long n,m;
	long long a[N][N];
	matrix()
	{
		n=m=0;
		memset(a,0,sizeof(a));
	}
	void clear()
	{
		n=m=0;
		memset(a,0,sizeof(a));
	}
	matrix& operator+=(matrix x)
	{
		fr(i,1,n)
			fr(j,1,m)
				a[i][j]=(a[i][j]+x.a[i][j])%p;
		return *this;
	}
	matrix operator+(matrix x)
	{
		x+=*this;
		return x;
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
	matrix operator*(long long c)
	{
		matrix x=*this;
		fr(i,1,n)
			fr(j,1,m)
				x.a[i][j]=x.a[i][j]*c%p;
		return x;
	}
	matrix& operator*=(long long c)
	{
		return *this=*this*c;
	}
}E,a,b,ans;
matrix operator*(long long c,matrix x)
{
	return x*c;
}
void initc(long long p)
{
	c[0]=0;
	for(long long i=2;i*i<=p;i++)
		if(p%i==0)
		{
			c[++c[0]]=i;
			while(p%i==0)
				p/=i;
		}
	if(p!=1)
		c[++c[0]]=p;
}
long long check()
{
	fr(i,1,c[0])
		if(power(g,p/c[i],p)==1)
			return 0;
	return 1;
}
void init()
{
	if(p<=3)
		g=p-1;
	else
	{
		g=1;
		while(!check())
			g++;
	}
	wk=power(g,(p-1)/k,p);
}
matrix getE(long long n)
{
	matrix E;
	E.n=E.m=n;
	fr(i,1,n)
		E.a[i][i]=1;
	return E;
}
matrix power(matrix a,long long b)
{
	matrix r=getE(a.n);
	while(b)
	{
		if(b&1)
			r*=a;
		a*=a;
		b>>=1;
	}
	return r;
}
int main()
{
	long long T=read();
	E=getE(2);
	b.n=b.m=2;
	b.a[1][1]=b.a[1][2]=b.a[2][1]=1;
	ans.n=2;
	ans.m=1;
	ans.a[1][1]=ans.a[2][1]=1;
	while(T--)
	{
		n=read();
		k=read();
		p=read();
		initc(p-1);
		init();
//		fr(i,1,c[0])
//			printf("%lld%c",c[i],i==c[0]?'\n':' ');
//		printf("%lld %lld\n",g,wk);
		a.clear();
		a.n=a.m=2;
		long long w=1;
		fr(i,0,k-1)
		{
			a+=power(E+b*w,n);
			w=w*wk%p;
		}
		a*=power(k,p-2,p);
		printf("%lld\n",(a*ans).a[2][1]);
	}
	return 0;
}
