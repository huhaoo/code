/**************************************************************
	File name: 1919.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/5/2018, 2:14:46 PM
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
#define B 21
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
int n,l,r[N],d[N];
double pi=acos(-1.0);
char s[N];
void fft(complex *a,int l,int opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		complex wn=complex(cos(pi/(1<<i)),opt*sin(pi/(1<<i)));
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			complex w=complex(1,0);
			fr(k,0,(1<<i)-1)
			{
				complex x=a[j+k],y=w*a[j+(1<<i)+k];
				a[j+k]=x+y;
				a[j+(1<<i)+k]=x-y;
				w=w*wn;
			}
		}
	}
}
int main()
{
	n=read()-1;
	scanf("%s",s);
	fr(i,0,n)a[i].real()=s[n-i]-'0';
	scanf("%s",s);
	fr(i,0,n)b[i].real()=s[n-i]-'0';
	l=0;
	while(n+n>=(1<<l))l++;
	fr(i,0,(1<<l)-1)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fft(a,l,1);
	fft(b,l,1);
	fr(i,0,(1<<l)-1)c[i]=a[i]*b[i];
	fft(c,l,-1);
	fr(i,0,n+n)d[i]=int(c[i].real()/(1<<l)+0.5);
	fr(i,0,n+n)
	{
		d[i+1]+=d[i]/10;
		d[i]%=10;
	}
	int ll=n+n+1;
	while(!d[ll])ll--;
	fr(i,0,ll)putchar(d[ll-i]+'0');
	return 0;
}