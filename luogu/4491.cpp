/***************************************************************
	File name: 4491.cpp
	Author: huhao
	Create time: Tue 15 Oct 2019 08:10:28 AM CST
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
const i64 N=(1<<19)|10,mod=1004535809,g=3;
const i64 gi=power(g,mod-2,mod);
namespace C
{
	const int N=20000010;
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
	i64 C(i64 a,i64 b)
	{
		return a<b?0:f[a]*F[b]%mod*F[a-b]%mod;
	}
}
i64 r[N],l;
void init(int n)
{
	l=0;
	while((1<<l)<n)
		l++;
	fr(i,0,(1<<l)-1)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
}
void NTT(i64 *a,i64 opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		i64 wn=power(opt==1?g:gi,(mod-1)>>(i+1),mod);
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			i64 w=1;
			fr(k,0,(1<<i)-1)
			{
				i64 x=a[j+k],y=a[j+k+(1<<i)]*w%mod;
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
i64 n,m,s,ans;
i64 A[N],B[N],w[N];
int main()
{
	n=read();
	m=read();
	s=read();
	fr(i,0,m)
		w[i]=read();
	i64 k=min(m,n/s);
	C::init(n+m);
	fr(i,0,k)
		A[i]=C::f[i]*C::f[s*i]%mod*power(C::F[s],i,mod)%mod*C::C(m,i)%mod*C::C(n,s*i)%mod*power(m-i,n-s*i,mod)%mod;
	fr(i,0,k)
		B[i]=(i%2==0?1:mod-1)*C::F[i]%mod;
	reverse(B,B+k+1);
	init(k+k+2);
	NTT(A,1);
	NTT(B,1);
	fr(i,0,(1<<l)-1)
		B[i]=A[i]*B[i]%mod;
	NTT(B,-1);
	fr(i,0,k)
		A[i]=B[i+k]*C::F[i]%mod;
	fr(i,0,k)
		ans=(ans+A[i]*w[i])%mod;
	printf("%lld\n",ans);
	return 0;
}
/*
2 2 2
1 2 3
 */
