/***************************************************************
	File name: 4723.cpp
	Author: huhao
	Create time: Mon 08 Jul 2019 04:58:58 PM CST
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
		if(b&1)
			r=r*a%p;
		a=a*a%p;
		b>>=1;
	}
	return r;
}
const int N=(1ll<<16)+10,mod=998244353,g=3,p=power(g,mod-2,mod);
i64 n,st[N],a[N],b[N],c[N],ans,l,r[N],k;
void NTT(i64 *a,int opt)
{
	fr(i,0,(1<<l)-1)
		if(i>r[i])
			swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		i64 wn=power(opt==1?g:p,(mod-1)>>(i+1),mod);
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
		i64 inv=power(1<<l,mod-2,mod);
		fr(i,0,(1<<l)-1)
			a[i]=a[i]*inv%mod;
	}
}
i64 _a[N],_b[N];
void mul(i64 *c,i64 *a,i64 *b,i64 na,i64 nb)
{
	l=0;
	while((1<<l)<na+nb+1)
		l++;
	fr(i,0,(1<<l)-1)
		_a[i]=_b[i]=0;
	fr(i,1,(1<<l)-1)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,0,na)
		_a[i]=a[i];
	fr(i,0,nb)
		_b[i]=b[i];
	NTT(_a,1);
	NTT(_b,1);
	fr(i,0,(1<<l)-1)
		_a[i]=_a[i]*_b[i]%mod;
	NTT(_a,-1);
	fr(i,0,na+nb)
		c[i]=_a[i];
}
i64 _c[N];
void inv(i64 *b,i64 *a,i64 n)
{
	if(n==1)
	{
		b[0]=power(a[0],mod-2,mod);
		return;
	}
	inv(b,a,(n+1)/2);
	mul(_c,b,a,n-1,n-1);
	fr(i,n,n+n)
		_c[i]=0;
	fr(i,0,n-1)
		_c[i]=(mod-_c[i])%mod;
	_c[0]=(_c[0]+2)%mod;
	mul(b,_c,b,n-1,n-1);
	fr(i,n,n+n)
		b[i]=0;
}
void reverse(i64 *l,i64 *r)
{
	while(l<r)
	{
		swap(*l,*r);
		l++;
		r--;
	}
}
i64 _d[N],_e[N];
void polymod(i64 *c,i64 *a,i64 *b,i64 n,i64 m)
{
	i64 l=n-m;
	reverse(a,a+n);
	reverse(b,b+m);
	inv(_d,b,l+1);
	mul(_d,_d,a,l,l);
	reverse(a,a+n);
	reverse(b,b+m);
	reverse(_d,_d+l);
	mul(_e,_d,b,l,m);
	fr(i,0,m-1)
		_e[i]=(a[i]-_e[i]+mod)%mod;
	fr(i,0,m-1)
		c[i]=_e[i];
}
int main()
{
	k=read();
	n=read();
	fr(i,1,n)
		a[n-i]=(-read()+mod)%mod;
	a[n]=1;
	fr(i,0,n-1)
		st[i]=(read()+mod)%mod;
	b[1]=1;
	c[0]=1;
	while(k)
	{
		if(k&1)
		{
			mul(c,b,c,n-1,n-1);
			polymod(c,c,a,n+n-2,n);
		}
		mul(b,b,b,n-1,n-1);
		polymod(b,b,a,n+n-2,n);
		k>>=1;
	}
	fr(i,0,n-1)
		ans=(ans+c[i]*st[i])%mod;
	printf("%lld\n",ans);
	return 0;
}
