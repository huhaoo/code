/**************************************************************
	File name: 4512.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 9/23/2018, 2:57:29 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define N 400010
#define mod 998244353
#define ll unsigned long long
#define fr(i,a,b) for(ll i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(ll i=(a),_end_=(b);i>=_end_;i--)
ll read()
{
	ll r=0,c=getchar();
	while(c<'0'||c>'9')
		c=getchar();
	while(c>='0'&&c<='9')
	{
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r;
}
ll power(ll x,ll y,ll p)
{
	ll r=1;
	while(y)
	{
		if(y&1)r=r*x%p;
		y>>=1;
		x=x*x%p;
	}
	return r;
}
ll r[N],q[N],f[N],g[N],rg[N],rf[N],g1[N],_[N],n,m;
ll v=3,w=power(v,mod-2,mod);
void NTT(ll *a,ll l,int opt)
{
	fr(i,0,(1<<l)-1)if(i<r[i])swap(a[i],a[r[i]]);
	fr(i,0,l-1)
	{
		ll wn=power(opt==1?v:w,(mod-1)>>(i+1),mod);
		for(ll j=0;j<(1ull<<l);j+=(1ull<<(i+1)))
		{
			ll w=1;
			fr(k,0,(1<<i)-1)
			{
				ll x=a[j+k],y=w*a[(1<<i)+j+k]%mod;
				a[j+k]=(x+y)%mod;a[(1<<i)+j+k]=(x-y+mod)%mod;
				w=w*wn%mod;
			}
		}
	}
	if(opt==-1)
	{
		ll inv=power((1<<l),mod-2,mod);
		fr(i,0,(1<<l)-1)a[i]=a[i]*inv%mod;
	}
}
void inv(ll *a,ll *b,ll n)
{
	if(n==1){b[0]=power(a[0],mod-2,mod);return;}
	inv(a,b,(n+1)>>1);
	ll l=0;
	while((1ull<<l)<=(n<<1))l++;
	fr(i,0,(1<<l)-1)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,0,n-1)_[i]=a[i];
	fr(i,n,(1<<l)-1)_[i]=0;
	NTT(b,l,1);NTT(_,l,1);
	fr(i,0,(1<<l)-1)b[i]=(2*b[i]%mod-b[i]*b[i]%mod*_[i]%mod+mod)%mod;
	NTT(b,l,-1);
	fr(i,n,(1<<l)-1)b[i]=0;
}
void rev(ll *l,ll *r)
{
	while(l<r){swap(*l,*r);l++;r--;}
}
int main()
{
	n=read();m=read();
	fr(i,0,n)f[i]=rf[n-i]=read();
	fr(i,0,m)g[i]=rg[m-i]=read();
	fr(i,n-m+1,n)rg[i]=0;
	inv(rg,g1,n-m+1);
	ll l=0;
	while((1ull<<l)<=(n<<1))l++;
	fr(i,0,(1<<l)-1)r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
	fr(i,n+1,(1<<l)-1)rf[i]=0;
	fr(i,n-m+1,(1<<l)-1)g1[i]=0;
	NTT(rf,l,1);NTT(g1,l,1);
	fr(i,0,(1<<l)-1)q[i]=rf[i]*g1[i]%mod;
	NTT(q,l,-1);
	rev(q,q+n-m);
	fr(i,n-m+1,(1<<l)-1)q[i]=0;
	fr(i,0,n-m)printf("%llu%c",q[i],i==n-m?'\n':' ');
	NTT(q,l,1);NTT(g,l,1);
	fr(i,0,(1<<l)-1)g[i]=g[i]*q[i]%mod;
	NTT(g,l,-1);
	fr(i,0,m-1)f[i]=(f[i]-g[i]+mod)%mod;
	fr(i,0,m-1)printf("%llu%c",f[i],i==m-1?'\n':' ');
	return 0;
}
#undef N
#undef ll
#undef mod