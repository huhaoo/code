/***************************************************************
	File name: 5641.cpp
	Author: huhao
	Create time: Mon 11 Nov 2019 07:16:58 PM CST
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
	a%=p;
	while(b)
	{
		if(b&1) r=r*a%p;
		a=a*a%p; b>>=1;
	}
	return r;
}
const i64 mod=998244353,g=3,gi=power(g,mod-2,mod);
inline i64& Add(i64& a,i64 b){return a=(a+b%mod+mod)%mod;}
/*
namespace bf
{
	const int N=100010;
	i64 n,k,a[N];
	int main()
	{
		n=read();k=read()-1;
		::C::init(n+k+1);
		fr(i,1,n) a[i]=read();
		fr(i,1,n)
		{
			i64 ans=0;
			fr(j,1,i) Add(ans,a[j]*::C::C(j+k-1,k)%mod*::C::C(i-j+k,k));
			printf("%lld%c",ans,i==n?'\n':' ');
		}
		return 0;
	}
}
 */
const int N=(1<<18)|10;
i64 n,k,a[N],c[N],f[N],F[N],l,r[N];
void init(int n)
{
	l=0;
	while((1<<l)<n) l++;
	fr(i,0,(1<<l)-1) r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
}
void NTT(i64 *a,int opt)
{
	fr(i,0,(1<<l)-1) if(i<r[i])
		swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		i64 wn=power(opt==1?g:gi,(mod-1)>>(i+1),mod);
		for(int j=0;j<(1<<l);j+=(1<<(i+1)))
		{
			i64 w=1;
			fr(k,0,(1<<i)-1)
			{
				i64 x=a[j+k],y=w*a[j+k+(1<<i)]%mod;
				a[j+k]=(x+y)%mod; a[j+k+(1<<i)]=(x-y+mod)%mod; w=w*wn%mod;
			}
		}
	}
	if(opt==-1)
	{
		i64 I=power(1<<l,mod-2,mod);
		fr(i,0,(1<<l)-1) a[i]=a[i]*I%mod;
	}
}
int main()
{
	n=read(); k=read()-1;
	fr(i,1,n) a[i]=read();
	c[0]=f[0]=1;
	fr(i,1,n)
	{
		c[i]=c[i-1]*(i+k)%mod;
		f[i]=f[i-1]*i%mod;
	}
	F[n]=power(f[n],mod-2,mod);
	fd(i,n,1) F[i-1]=F[i]*i%mod;
	fr(i,0,n) c[i]=c[i]*F[i]%mod;
	fr(i,1,n) a[i]=a[i]*c[i-1]%mod;
	init(n+n+1);
	NTT(a,1); NTT(c,1);
	fr(i,0,(1<<l)-1) a[i]=a[i]*c[i]%mod;
	NTT(a,-1);
	fr(i,1,n) printf("%lld%c",a[i],i==n?'\n':' ');
	return 0;
}
