/***************************************************************
	File name: 5401.cpp
	Author: huhao
	Create time: Thu 19 Sep 2019 01:51:52 PM CST
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
	a=(a%p+p)%p;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
const int mod=998244353,g=3,G=power(3,mod-2,mod),i2=power(2,mod-2,mod);
const int N=1<<19|10;
i64 d,n,m,a,f[N],F[N],p[N],ans,A[N],B[N],l,r[N];
i64 C(i64 n,i64 m)
{
	return f[n]*F[m]%mod*F[n-m]%mod;
}
i64 _a[N],_b[N];
void NTT(i64 *a,int opt)
{
	fr(i,1,(1<<l)-1)
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
void mul(i64 *ans,i64 *a,i64 *b,i64 n,i64 m)
{
	l=0;
	while((1<<l)<(n+m+1))
		l++;
	fr(i,1,(1<<l)-1)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,0,(1<<l)-1)
		_a[i]=_b[i]=0;
	fr(i,0,n)
		_a[i]=a[i];
	fr(i,0,m)
		_b[i]=b[i];
	NTT(_a,1);
	NTT(_b,1);
	fr(i,0,(1<<l)-1)
		ans[i]=_a[i]*_b[i]%mod;
	NTT(ans,-1);
}
int main()
{
	d=read();
	n=read();
	m=read();
	a=n-m*2;
	f[0]=1;
	fr(i,1,d)
		f[i]=f[i-1]*i%mod;
	F[d]=power(f[d],mod-2,mod);
	fd(i,d,1)
		F[i-1]=F[i]*i%mod;
	fr(i,0,d)
	{
		A[i]=F[i];
		B[i]=(power(d-2*i,n,mod)*F[i]%mod*(i&1?-1:1)+mod)%mod;
	}
	mul(A,A,B,d,d);
	fr(i,0,d)
	{
		A[i]=power(i2,i,mod)*C(d,i)%mod*f[i]%mod*A[i]%mod*f[i]%mod;
		B[d-i]=((i&1?-1:1)*F[i]+mod)%mod;
	}
	mul(A,A,B,d,d);
	fr(i,0,min(a,d))
		ans=(ans+A[d+i]*F[i])%mod;
	printf("%lld\n",ans);
	return 0;
}
