/**************************************************************
	File name: 4229.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 2/27/2019, 9:12:58 AM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(long long i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(long long i=(a),_end_=(b);i>=_end_;i--)
long long read()
{
	long long r=0,t=1,c=getchar();
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
#define N 2010
#define mod 998244353
#include<map>
long long T;
long long n,q,m,p[N],c,f[N][N],v[N],h[N],l[N],w[N],ans,s,k[N];
struct query
{
	long long l,r,h;
	query(long long _l=0,long long _r=0,long long _h=0)
	{
		l=_l;
		r=_r;
		h=_h;
	}
}a[N];
long long pow(long long a,long long b,long long p)
{
	long long r=1;
	while(b)
	{
		if(b&1)
			r=r*a%p;
		b>>=1;
		a=a*a%p;
	}
	return r;
}
long long inv(long long a)
{
	return pow(a,mod-2,mod);
}
map<long long,long long>t;
long long calc(long long w)
{
	long long r=0;
	s=0;
	fr(i,1,n)
		if(h[i]==w)
		{
			k[++s]=i;
			l[s]=0;
			memset(f[s],0,sizeof(f[s]));
		}
	fr(i,1,q)
		if(a[i].h==w)
		{
			if(!s)
				return 0;
			long long _l=lower_bound(k+1,k+s+1,a[i].l)-k,_r=lower_bound(k+1,k+s+1,a[i].r)-k-1;
			if(_r<_l)
				return 0;
			l[_r]=max(l[_r],_l);
		}
	f[0][0]=1;
	fr(i,1,s)
	{
		long long c1=pow(w,v[k[i]+1]-v[k[i]],mod),c2=pow(w-1,v[k[i]+1]-v[k[i]],mod);
		fr(j,0,i-1)
			if(f[i-1][j])
			{
				if(j>=l[i])
					f[i][j]=f[i-1][j]*c2%mod;
				f[i][i]=(f[i][i]+f[i-1][j]*(c1-c2+mod))%mod;
			}
	}
	fr(i,0,s)
		r=(r+f[s][i])%mod;
	return r;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		q=read();
		m=read();
		p[c=1]=1;
		p[c=2]=n+1;
		ans=1;
		fr(i,1,q)
		{
			a[i].l=read();
			a[i].r=read()+1;
			a[i].h=read();
			p[++c]=a[i].l;
			p[++c]=a[i].r;
			w[i]=a[i].h;
		}
		sort(p+1,p+c+1);
		sort(w+1,w+q+1);
		t.clear();
		n=0;
		fr(i,1,c)
			if(p[i]!=p[i-1])
			{
				t[p[i]]=++n;
				v[n]=p[i];
			}
		n--;
		fr(i,1,q)
		{
			a[i].l=t[a[i].l];
			a[i].r=t[a[i].r];
		}
		fr(i,1,n)
			h[i]=m+1;
		fr(i,1,q)
			fr(j,a[i].l,a[i].r-1)
				h[j]=min(h[j],a[i].h);
		fr(i,1,q)
			if(w[i]!=w[i-1])
			{
				ans=ans*calc(w[i])%mod;
				if(!ans)
					break;
			}
		fr(i,1,n)
			if(h[i]==m+1)
				ans=ans*pow(m,v[i+1]-v[i],mod)%mod;
		printf("%lld\n",ans);
	}
	return 0;
}