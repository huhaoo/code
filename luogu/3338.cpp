/**************************************************************
	File name: 3338.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/13/2018, 6:07:46 PM
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
#define N 400000
int n,l=0,r[N];
double q[N],ans[N];
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
double pi=acos(-1.0);
void FFT(complex *a,int opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		complex wn;wn={cos(pi/(1<<i)),opt*sin(pi/(1<<i))};
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			complex w;w={1,0};
			fr(k,0,(1<<i)-1)
			{
				complex x=a[j+k],y=w*a[j+k+(1<<i)];
				a[j+k]=x+y;
				a[j+k+(1<<i)]=x-y;
				w*=wn;
			}
		}
	}
	if(opt==-1)
		fr(i,0,(1<<l)-1)
			a[i].real()/=1<<l;
}
int main()
{
	n=read();
	fr(i,1,n)scanf("%lf",q+i);
	while((1<<l)<=n+n)l++;
	fr(i,0,(1<<l)-1)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,0,(1<<l)-1)a[i]=b[i]=c[i]={0,0};
	fr(i,1,n)a[i]={q[i],0};
	fr(i,1,n)b[i]={1./i/i,0};
	FFT(a,1);FFT(b,1);
	fr(i,0,(1<<l)-1)c[i]=a[i]*b[i];
	FFT(c,-1);
	fr(i,1,n)ans[i]=c[i].real();
	fr(i,0,(1<<l)-1)a[i]=b[i]=c[i]={0,0};
	fr(i,1,n)a[n+1-i]={q[i],0};
	fr(i,1,n)b[i]={1./i/i,0};
	FFT(a,1);FFT(b,1);
	fr(i,0,(1<<l)-1)c[i]=a[i]*b[i];
	FFT(c,-1);
	fr(i,1,n)ans[i]-=c[n-i+1].real();
	fr(i,1,n)printf("%lf\n",ans[i]);
	return 0;
}