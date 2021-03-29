/***************************************************************
	File name: 5434.cpp
	Author: huhao
	Create time: Fri 11 Oct 2019 08:12:40 AM CST
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
const int mod=998244353,N=(2<<19)|10;
const i64 g=3;
const i64 gi=power(g,mod-2,mod);
i64 r[N],l,wn[20][N],Wn[20][N],L;
void init(i64 n)
{
	l=0;
	while((1<<l)<n)
		l++;
	fr(i,0,(1<<l)-1)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
}
i64 Mod(i64 a)
{
	return a>=mod?a-mod:a;
}
void NTT(i64 *a,i64 opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
			fr(k,0,(1<<i)-1)
			{
				i64 x=a[j+k],y=(opt==1?wn:Wn)[i][k]*a[j+k+(1<<i)]%mod;
				a[j+k]=Mod(x+y);
				a[j+k+(1<<i)]=Mod(x-y+mod);
			}
	if(opt==-1)
	{
		i64 I=power(1<<l,mod-2,mod);
		fr(i,0,(1<<l)-1)
			a[i]=a[i]*I%mod;
	}
}
i64 I1[N],I2[N];
void inv(i64 *b,i64 *a,i64 n)
{
	if(n==1)
	{
		*b=power(*a,mod-2,mod);
		return;
	}
	i64 n0=(n+1)>>1;
	inv(b,a,n0);
	init(n+n);
	fr(i,0,(1<<l)-1)
		I1[i]=I2[i]=0;
	fr(i,0,n-1)
		I1[i]=a[i];
	fr(i,0,n0-1)
		I2[i]=b[i];
	NTT(I1,1);
	NTT(I2,1);
	fr(i,0,(1<<l)-1)
		I1[i]=I1[i]*I2[i]%mod*I2[i]%mod;
	NTT(I1,-1);
	fr(i,0,n-1)
		b[i]=(2*b[i]-I1[i]+mod)%mod;
}
namespace Choose
{
	i64 f[N],F[N];
	void init(int n)
	{
		f[0]=1;
		fr(i,1,n)
			f[i]=f[i-1]*i%mod;
		F[n]=power(f[n],mod-2,mod);
		fd(i,n,1)
			F[i-1]=F[i]*i%mod;
	}
	i64 inv(i64 n)
	{
		return F[n]*f[n-1]%mod;
	}
}
void integral(i64 *b,i64 *a,i64 n)
{
	fr(i,1,n-1)
		b[i]=a[i-1]*Choose::inv(i)%mod;
	b[0]=0;
}
void dx(i64 *b,i64 *a,i64 n)
{
	fr(i,0,n-2)
		b[i]=a[i+1]*(i+1)%mod;
	b[n-1]=0;
}
i64 L1[N],L2[N];
void ln(i64 *b,i64 *a,i64 n)
{
	init(n+n);
	fr(i,0,(1<<l)-1)
		L1[i]=L2[i]=0;
	dx(L2,a,n);
	inv(L1,a,n);
	init(n+n);
	NTT(L1,1);
	NTT(L2,1);
	fr(i,0,(1<<l)-1)
		L1[i]=L1[i]*L2[i]%mod;
	NTT(L1,-1);
	integral(b,L1,n);
}
i64 E1[N],E2[N];
void exp(i64 *b,i64 *a,i64 n)
{
	if(n==1)
	{
		*b=1;
		return;
	}
	i64 n0=(n+1)>>1;
	exp(b,a,n0);
	init(n+n);
	fr(i,0,(1<<l)-1)
		E1[i]=E2[i]=0;
	fr(i,n0,n-1)
		b[i]=0;
	ln(E1,b,n);
	fr(i,0,n-1)
		E1[i]=((i==0)-E1[i]+a[i]+mod)%mod;
	fr(i,0,n0-1)
		E2[i]=b[i];
	init(n+n);
	NTT(E1,1);
	NTT(E2,1);
	fr(i,0,(1<<l)-1)
		E1[i]=E1[i]*E2[i]%mod;
	NTT(E1,-1);
	fr(i,0,n-1)
		b[i]=E1[i];
}
i64 A[N],B[N],C[N],D[N],E[N],F[N],G[N],H[N];
void solve(i64 *a,i64 n)
{
	if(n==1)
	{
		a[0]=0;
		return;
	}
	i64 n0=(n+1)>>1;
	solve(a,n0);
	init(n+n);
	fr(i,0,(1<<l)-1)
		A[i]=B[i]=C[i]=D[i]=E[i]=F[i]=G[i]=H[i]=0;
	fr(i,0,n-1)
		A[i]=a[i];
	NTT(A,1);
	fr(i,0,(1<<l)-1)
		A[i]=A[i]*A[i]%mod;
	NTT(A,-1);
	//A=A0^2
	fr(i,0,n-1)
		A[i]=(2*a[i]-A[i]+mod)%mod;
	//A=2A0-A0^2
	fr(i,0,n-1)
		B[i]=(-2*a[i]+(i==0?2:0))%mod;
	//B=2-2A0
	inv(C,B,n);
	init(n+n);
	NTT(A,1);
	NTT(C,1);
	fr(i,0,(1<<l)-1)
		A[i]=A[i]*C[i]%mod;
	NTT(A,-1);
	exp(D,A,n);
	//D=exp(A/B)
	fd(i,n-1,1)
		D[i]=D[i-1];
	D[0]=0;
	fr(i,0,n-1)
		E[i]=((i==0)-a[i]+mod)%mod;
	init(n+n);
	NTT(E,1);
	fr(i,0,(1<<l)-1)
		E[i]=E[i]*E[i]%mod;
	NTT(E,-1);
	inv(F,E,n);
	//F=1/(1-A0(x))^2
	F[0]=(F[0]+1)%mod;
	init(n+n);
	NTT(F,1);
	fr(i,0,n-1)
		G[i]=D[i];
	NTT(G,1);
	fr(i,0,(1<<l)-1)
		G[i]=G[i]*F[i]%mod;
	NTT(G,-1);
	fr(i,0,n-1)
		G[i]=((i==0?2:0)-G[i]+mod)%mod;
	inv(H,G,n);
	fr(i,0,n-1)
		D[i]=(2*a[i]-2*D[i]+mod*2)%mod;
	init(n+n);
	NTT(H,1);
	NTT(D,1);
	fr(i,0,(1<<l)-1)
		D[i]=D[i]*H[i]%mod;
	NTT(D,-1);
	fr(i,0,n-1)
		a[i]=(a[i]-D[i]+mod)%mod;
}
i64 a[N],n,b[N];
int main()
{
	n=131072;
	Choose::init(n+n);
	L=18;
	fr(i,0,L-1)
	{
		wn[i][0]=Wn[i][0]=1;
		wn[i][1]=power(g,(mod-1)>>(i+1),mod);
		Wn[i][1]=power(gi,(mod-1)>>(i+1),mod);
		fr(j,2,(1<<(i+1))-1)
		{
			wn[i][j]=wn[i][j-1]*wn[i][1]%mod;
			Wn[i][j]=Wn[i][j-1]*Wn[i][1]%mod;
		}
	}
	solve(a,n);
	fr(i,1,n-1)
		a[i]=a[i]*Choose::F[i]%mod*Choose::f[i-1]%mod;
	exp(b,a,n);
	n=read();
	printf("%lld\n",b[n]*Choose::f[n]%mod);
	return 0;
}
