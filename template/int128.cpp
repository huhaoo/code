/***************************************************************
	File name: int128.cpp
	Author: huhao
	Create time: Wed 04 Nov 2020 10:02:15 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
#define u64 unsigned long long
struct u128
{
	u64 b1,b0;
	u128(){ b0=b1=0; }
	template<class T> u128(T x){ b1=0; b0=x; }
	u128(u64 x,u64 y){ b1=x; b0=y; }
	operator bool(){ return b0||b1; }
	operator u64(){ return b0; }
	operator int(){ return b0&(-1u); }
};
u128 operator>>(u128 a,int b)
{
	if(!b) return a;
	else if(b>=64) return u128(0,a.b1>>(b-64));
	else return u128(a.b1>>b,a.b0>>b|a.b1<<(64-b));
}
u128 operator<<(u128 a,int b)
{
	if(!b) return a;
	else if(b>=64) return u128(a.b0<<(b-64),0);
	else return u128(a.b1<<b|a.b0>>(64-b),a.b0<<b);
}
u128 operator&(u128 a,u128 b){ return u128(a.b1&b.b1,a.b0&b.b0); }
u128 operator|(u128 a,u128 b){ return u128(a.b1|b.b1,a.b0|b.b0); }
u128 operator*(u128 a,u128 b)
{
	u64 A[4]={a.b1>>32,a.b1&(-1u),a.b0>>32,a.b0&(-1u)},B[4]={b.b1>>32,b.b1&(-1u),b.b0>>32,b.b0&(-1u)};
	u64 C[5]={0,0,0,0,0};
	fr(i,0,3) fr(j,0,3)
	{
		u64 d=A[i]*B[j],p=6-(i+j);
		while(p<=3)
		{
			C[p]+=d; if(C[p]<d){ p++; d=1; } else break;
		}
	}
	fd(i,3,0){ C[i+1]+=C[i]>>32; C[i]&=-1u; }
	fr(i,0,3){ C[i+1]+=C[i]>>32; C[i]&=-1u; }
	return u128(C[3]<<32|C[2],C[1]<<32|C[0]);
}
u128 operator+(u128 a,u128 b)
{
	u128 c(a.b1+b.b1,a.b0+b.b0);
	if(c.b0<a.b0) c.b1++;
	return c;
}
template<class T> u128 operator+(u128 a,T b){ return a+u128(b); }
template<class T> u128 operator*(u128 a,T b){ return a*u128(b); }
template<class T> u128 operator|(u128 a,T b){ return a|u128(b); }
template<class T> u128 operator&(u128 a,T b){ return a&u128(b); }
template<class T> u128 operator+(T b,u128 a){ return a+u128(b); }
template<class T> u128 operator*(T b,u128 a){ return a*u128(b); }
template<class T> u128 operator|(T b,u128 a){ return a|u128(b); }
template<class T> u128 operator&(T b,u128 a){ return a&u128(b); }

int main()
{
	return 0;
}
