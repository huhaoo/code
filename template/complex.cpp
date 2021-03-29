/**************************************************************
	File name: complex.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 7/4/2018, 7:13:45 PM
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
struct comp
{
	double real,imag;
	comp(double r=0.,double i=0.)
	{
		real=r;
		imag=i;
	}
	comp operator+(comp k){return comp(real+k.real,imag+k.imag);}
	comp& operator+=(comp k){return *this=*this+k;}
	comp operator-(comp k){return comp(real-k.real,imag-k.imag);}
	comp& operator-=(comp k){return *this=*this-k;}
	comp operator*(comp k){return comp(real*k.real-imag*k.imag,real*k.imag+imag*k.real);}
	comp& operator*=(comp k){return *this=*this*k;}
	comp operator*(double c){return comp(real*c,imag*c);}
	comp& operator*=(double c){return *this=*this*c;}
	comp operator/(double c){return comp(real/c,imag/c);}
	comp& operator/=(double c){return *this=*this/c;}
};
comp operator*(double c,comp i){return i*c;}
comp operator/(double c,comp i){return i/c;}
int main()
{
	return 0;
}
