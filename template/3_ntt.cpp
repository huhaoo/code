/***************************************************************
	File name: 3_ntt.cpp
	Author: huhao
	Create time: Wed 06 Nov 2019 11:46:41 AM CST
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
int check(i64 p)
{
	fr(i,2,sqrt(p))
		if(p%i==0)
			return 0;
	return 1;
}
i64 getg(i64 n)
{
	i64 a[20],c=0;
	i64 k=n-1;
	fr(i,2,sqrt(k))
		if(k%i==0)
		{
			a[++c]=i;
			while(k%i==0)
				k/=i;
			end_i=sqrt(k);
		}
	if(k!=1)
		a[++c]=k;
	fr(g,2,n)
	{
		int flag=1;
		fr(i,1,c)
			if(power(g,(n-1)/a[i],n)==1)
			{
				flag=0;
				break;
			}
		if(flag)
			return g;
	}
	return -1;
}
void find_ntt_mod(i64 p,i64 cnt,i64 g)//2^p|mod-1
{
	i64 i=1;
	while(cnt)
	{
		if(check((i<<p)+1)&&getg((i<<p)+1)==g)
		{
			printf("%lld*2^%lld=%lld,g=%lld\n",i,p,(i<<p)+1,getg((i<<p)+1));
			cnt--;
		}
		i++;
	}
}
const i64 N=(1<<19)|10;
i64 l,r[N];
void init(int n)
{
	l=0;
	while((1<<l)<n)
		l++;
	fr(i,0,(1<<l)-1)
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
}
struct calcNTT
{
	i64 mod,g,ig;
	void set(i64 Mod=0,i64 G=0)
	{
		mod=Mod;
		g=G;
		ig=power(g,mod-2,mod);
	}
	void NTT(i64 *a,i64 opt)
	{
		fr(i,0,(1<<l)-1)
			if(i<r[i])
				swap(a[i],a[r[i]]);
		fr(i,0,l-1)
		{
			i64 wn=power(opt==1?g:ig,(mod-1)>>(i+1),mod);
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
	i64 _a[N],_b[N];
	void mul(i64 *o,i64 *a,i64 *b,i64 n,i64 m)
	{
		init(n+m+1);
		fr(i,0,(1<<l)-1)
			_a[i]=_b[i]=o[i]=0;
		fr(i,0,n)
			_a[i]=a[i];
		fr(i,0,m)
			_b[i]=b[i];
		NTT(_a,1);NTT(_b,1);
		fr(i,0,(1<<l)-1)
			o[i]=_a[i]*_b[i]%mod;
		NTT(o,-1);
	}
}NTT1,NTT2,NTT3;
i64 o1[N],o2[N],o3[N];
void mul(i64 *o,i64 *a,i64 *b,i64 n,i64 m,i64 mod)
{
	NTT1.mul(o1,a,b,n,m);
	NTT2.mul(o2,a,b,n,m);
	NTT3.mul(o3,a,b,n,m);
	// o = o1 + m1 k1 = o2 + m2 k2 = o3 + m3 k3
	i64 m1=NTT1.mod,m2=NTT2.mod,m3=NTT3.mod;
	fr(i,0,n+m)
	{
		i64 k1=(o2[i]-o1[i]%m2+m2)%m2*power(m1,m2-2,m2)%m2;
		i64 _o=o1[i]+k1*m1;
		i64 _k=(o3[i]-_o%m3+m3)%m3*power(m1*m2%m3,m3-2,m3)%m3;
		o[i]=(_o%mod+_k%mod*m1%mod*m2%mod)%mod;
	}
}
i64 o[N],a[N],b[N],n,m,mod;
int main()
{
/*	printf("%lld\n",getg(998244353));
	find_ntt_mod(21,30,3);*/
	NTT1.set(469762049,3);
	NTT2.set(998244353,3);
	NTT3.set(1004535809,3);
	n=read();
	m=read();
	mod=read();
	fr(i,0,n)
		a[i]=read();
	fr(i,0,m)
		b[i]=read();
	mul(o,a,b,n,m,mod);
	fr(i,0,n+m)
		printf("%lld%c",o[i],i==n+m?'\n':' ');
	return 0;
}
