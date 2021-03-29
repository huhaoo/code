/***************************************************************
	File name: 循环卷积ntt.cpp
	Author: huhao
	Create time: Wed 02 Oct 2019 03:52:21 PM CST
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
#define i64 long long
i64 power(i64 a,i64 b,i64 p)
{
	i64 r=1;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
const i64 N=1<<20|10,mod=950009857,g=7;
const i64 G=power(g,mod-2,mod);
void checkg()
{
	i64 _g=1;
	fr(i,1,mod-2)
		if((_g=_g*g%mod)==1)
		{
			printf("%lld^%d=1\n",g,i);
			return;
		}
	printf("%lld is accepted!\n",g);
}
i64 r[N],l;
void NTT(i64 *a,i64 opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		i64 wn=power(opt==1?g:G,(mod-1)>>(i+1),mod);
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			i64 w=1;
			fr(k,0,(1<<i)-1)
			{
				i64 x=a[j+k],y=w*a[j+k+(1<<i)]%mod;
				a[j+k]=(x+y)%mod;
				a[j+k+(1<<i)]=(x-y+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
	if(opt==-1)
	{
		i64 I=power(1<<l,mod-2,mod);
		fr(i,0,(1<<l)-1)
			a[i]=a[i]*I%mod;
	}
}
void init(i64 n)
{
	l=0;
	while((1<<l)<n)
		l++;
	fr(i,1,(1<<l)-1)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
}
i64 A[N],B[N];
void mul(i64 *c,i64 *a,i64 *b,i64 n,i64 m)
{
	fr(i,0,(1<<l)-1)
		A[i]=B[i]=0;
	fr(i,0,n)
		A[i]=a[i];
	fr(i,0,m)
		B[i]=b[i];
	NTT(A,1);
	NTT(B,1);
	fr(i,0,(1<<l)-1)
		c[i]=A[i]*B[i]%mod;
	NTT(c,-1);
}
i64 _A[N],_B[N];
void DFT(i64 *b,i64 *a,i64 L,i64 opt)
{
	i64 wn=power(g,(mod-1)/(L*2),mod);
	i64 Wn=power(wn,mod-2,mod);
	fr(i,0,L*2-1)
		_A[i]=power(opt==-1?wn:Wn,(i-L)*(i-L),mod);
	fr(i,0,L-1)
		_B[i]=a[i]*power(opt==1?wn:Wn,i*i,mod)%mod;
	mul(b,_A,_B,L*2-1,L-1);
	fr(i,0,L-1)
		b[i]=b[i+L]*power(opt==1?wn:Wn,i*i,mod)%mod;
	fr(i,L,L*3-2)
		b[i]=0;
	if(opt==-1)
	{
		i64 I=power(L,mod-2,mod);
		fr(i,0,L-1)
			b[i]=b[i]*I%mod;
	}
}
i64 A_[N],B_[N],C_[N];
void Mul(i64 *c,i64 *a,i64 *b,i64 L)//2L|mod-1
{
	init(L*4);
	DFT(A_,a,L,1);
	DFT(B_,b,L,1);
	fr(i,0,L-1)
		C_[i]=A_[i]*B_[i]%mod;
	DFT(c,C_,L,-1);
}
int main()
{
	return 0;
}
