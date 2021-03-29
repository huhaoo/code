/***************************************************************
	File name: uint.cpp
	Author: huhao
	Create time: Wed 04 Nov 2020 10:39:30 AM CST
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
#define tw template<int w>
template<int w> struct Int // 0~2^(32w)-1
{
	u64 a[w+2];
	Int(u64 v=0){ memset(a,0,sizeof(a)); a[0]=v&(-1u); a[1]=v>>32; }
	u64 &operator[](int p){ return a[p]; }
	operator int(){ return a[0]; }
	operator u64(){ return a[0]|a[1]<<32; }
};
tw Int<w> operator+(Int<w> a,Int<w> b)
{
	fr(i,0,w-1) a[i]+=b[i];
	fr(i,0,w-1) if(a[i]>(-1u)){ a[i+1]+=a[i]>>32; a[i]&=-1u; }
	return a;
}
template<class T,int w> Int<w> operator*(Int<w> a,T b)
{
	fr(i,0,w-1) a[i]*=b;
	fr(i,0,w-1) if(a[i]>(-1u)){ a[i+1]+=a[i]>>32; a[i]&=-1u; }
	return a;
}
tw Int<w> operator<<(Int<w> a,int b)
{
	Int<w> A; int x=b>>5,y=b&31;
	fr(i,0,w-1-x){ A[i+x]|=a[i]<<y; }
	fr(i,0,w-2-x){ A[i+x+1]|=a[i]>>(32-y); }
	fr(i,0,w-1) A[i]&=-1u;
	return A;
}
tw Int<w> operator>>(Int<w> a,int b)
{
	Int<w> A; int x=b>>5,y=b&31;
	fr(i,x,w-1){ A[i-x]|=a[i]>>y; }
	fr(i,x+1,w-1){ A[i-x-1]|=a[i]<<(32-y); }
	fr(i,0,w-1) A[i]&=-1u;
	return A;
}
tw Int<w> operator&(Int<w> a,Int<w> b)
{
	fr(i,0,w-1) a[i]&=b[i];
	return a;
}
tw Int<w> operator|(Int<w> a,Int<w> b)
{
	fr(i,0,w-1) a[i]|=b[i];
	return a;
}
template<class T,int w> T operator&(Int<w> a,T b){ return T(a&(Int<w>)b); }
template<class T,int w> T operator|(Int<w> a,T b){ return T(a|(Int<w>)b); }
template<class T,int w> Int<w> operator+(Int<w> a,T b){ return a+Int<w>(b); }
#undef tw

int main()
{
	return 0;
}
