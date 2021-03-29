/***************************************************************
	File name: binary.cpp
	Author: huhao
	Create time: Tue 03 Nov 2020 04:03:13 PM CST
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
#include<vector>
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
#define u128 Int<256/32>
const int W=256;
int n;
std::vector<u128> e[W+10];
u128 query(u128 a)
{
	u128 s=0;
	fd(i,W-1,0) s=s*10+((a>>i)&1);
	return s;
}
int main()
{
	freopen("binary.in","r",stdin); freopen("binary.out","w",stdout);
	n=read();
	fr(i,0,W-1) e[i].push_back((u128)1<<i);
	fr(i,0,W-1)
	{
		if(e[i].size()<n) n-=e[i].size();
		else
		{
			fd(j,i,0) putchar(48+((e[i][n-1]>>j)&1));
			putchar(10); return 0;
		}
		for(auto u:e[i])
		{
			u128 v=query(u);
			fr(j,i+1,W-1) if((v>>j)&1) break; else e[j].push_back(((u128)1<<j)|u);
		}
	}
	printf("%d\n",n);
	return 0;
}
