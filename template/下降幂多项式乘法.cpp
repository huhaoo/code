/**************************************************************
	File name: 5394.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2019/7/25 下午2:24:52
**************************************************************/
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
		r=(r<<3)+(r<<1)+(c^48);
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
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
const i64 N=(1<<20)+10,mod=998244353,g=3;
const i64 gi=power(g,mod-2,mod);
i64 n,m,a[N],b[N],c[N],l,r[N],f[N],pf[N],e[N],s;
i64 _a[N],_b[N];
void NTT(i64 *a,i64 opt)
{
	fr(i,0,(1<<l)-1)
		if(i<r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		i64 wn=power(opt==1?g:gi,(mod-1)>>(i+1),mod);
		for(i64 j=0;j<(1<<l);j+=(1<<(i+1)))
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
		i64 _i=power(1<<l,mod-2,mod);
		fr(i,0,(1<<l)-1)
			a[i]=a[i]*_i%mod;
	}
}
void mul(i64 *c,i64 *a,i64 *b,i64 n,i64 m)
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
		c[i]=_a[i]*_b[i]%mod;
	NTT(c,-1);
}
int main()
{
	n=read();
	m=read();
	s=n+m;
	f[0]=1;
	fr(i,1,s)
		f[i]=f[i-1]*i%mod;
	pf[s]=power(f[s],mod-2,mod);
	fd(i,s,1)
		pf[i-1]=pf[i]*i%mod;
	fr(i,0,s)
		e[i]=pf[i];
	fr(i,0,n)
		a[i]=read();
	mul(a,a,e,n,s);
	fr(i,0,s)
		e[i]=pf[i];
	fr(i,0,m)
		b[i]=read();
	mul(b,b,e,m,s);
	fr(i,0,s)
		c[i]=a[i]*b[i]%mod*f[i]%mod;
	fr(i,0,s)
		e[i]=(i%2==0)?pf[i]:(mod-pf[i])%mod;
	mul(c,c,e,s,s);
	fr(i,0,s)
		printf("%lld%c",c[i],i==s?'\n':' ');
	return 0;
}