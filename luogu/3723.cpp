/**************************************************************
	File name: 3723.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/5/2018, 4:56:10 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define N (1<<21)
struct complex
{
	double a,b;
	complex(double aa=0,double bb=0)
	{
		a=aa;
		b=bb;
	}
	complex operator+(complex k){return complex(a+k.a,b+k.b);}
	complex operator+=(complex k){return *this=*this+k;}
	complex operator-(complex k){return complex(a-k.a,b-k.b);}
	complex operator-=(complex k){return *this=*this-k;}
	complex operator*(complex k){return complex(a*k.a-b*k.b,a*k.b+b*k.a);}
	complex operator*=(complex k){return *this=*this*k;}
	double &real(){return a;}
	double &unreal(){return b;}
}a[N],b[N],c[N];
int n,l,x[N],y[N],ans,r[N];
int calc()
{
	int a=n,b=0;
	fr(i,1,n)b+=2*(x[i]-y[i]);
	int k1=-b/2/a,k2=-1-b/2/a,k3=1-b/2/a;
	return min(a*k1*k1+b*k1,min(a*k2*k2+b*k2,a*k3*k3+b*k3));
}
double pi=acos(-1.0);
void fft(complex *a,int opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		complex wn(cos(pi/(1<<i)),opt*sin(pi/(1<<i)));
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			complex w(1,0);
			fr(k,0,(1<<i)-1)
			{
				complex x=a[j+k],y=w*a[(1<<i)+j+k];
				a[j+k]=x+y;
				a[j+k+(1<<i)]=x-y;
				w=w*wn;
			}
		}
	}
}
int main()
{
	n=read();read();
	fr(i,1,n)x[i]=read();
	fr(i,1,n)y[i]=read();
	l=0;
	fr(i,0,2*n-1)a[i]={x[(n*2-i-1)%n+1]*1.0,0};
	fr(i,0,n-1)b[i]={y[i+1]*1.0,0};
	while((1<<l)<=(3*n-2))l++;
	fr(i,0,(1<<l)-1)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fft(a,1);
	fft(b,1);
	fr(i,0,(1<<l)-1)c[i]=a[i]*b[i];
	fft(c,-1);
	fr(i,-1,n-1)ans=min(ans,-2*int(c[n+i].real()/(1<<l)+0.5));
	fr(i,1,n)ans+=x[i]*x[i]+y[i]*y[i];
	ans+=calc();
	printf("%d\n",ans);
	return 0;
}