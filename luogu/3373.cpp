/****************************************************************
	File name: 3373.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 10/28/2018, 11:11:50 AM
****************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
#define N 200010
unsigned long long a,b,n,p,q,v[N],s[N],l1[N],l2[N];
int main()
{
	n=read();q=read();p=read();
	b=200;a=(n+b-1)/b;
	fr(i,1,n)v[i]=read();
	fr(i,1,a)
	{
		l1[i]=1;
		fr(j,0,b-1)s[i]+=v[i*b-j];
	}
	while(q--)
	{
		int opt=read();
		if(opt==1)
		{
			unsigned long long l=read(),r=read(),c=read(),L,R;
			L=(l+b-1)/b;R=(r+b-1)/b;
			if(L==R)
			{
				s[L]=0;
				fr(i,L*b-b+1,l-1)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L])%p))%p;
				fr(i,r+1,R*b)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L])%p))%p;
				fr(i,l,r)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L])*c%p))%p;
				l1[L]=1;l2[L]=0;
				continue;
			}
			fr(i,L+1,R-1)
			{
				s[i]=s[i]*c%p;
				l1[i]=l1[i]*c%p;
				l2[i]=l2[i]*c%p;
			}
			s[L]=s[R]=0;
			fr(i,L*b-b+1,l-1)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L])%p))%p;
			fr(i,l,L*b)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L])*c%p))%p;
			fr(i,R*b-b+1,r)s[R]=(s[R]+(v[i]=(v[i]*l1[R]+l2[R])*c%p))%p;
			fr(i,r+1,R*b)s[R]=(s[R]+(v[i]=(v[i]*l1[R]+l2[R])%p))%p;
			l1[L]=l1[R]=1;l2[L]=l2[R]=0;
		}
		if(opt==2)
		{
			unsigned long long l=read(),r=read(),c=read(),L,R;
			L=(l+b-1)/b;R=(r+b-1)/b;
			if(L==R)
			{
				s[L]=0;
				fr(i,L*b-b+1,l-1)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L])%p))%p;
				fr(i,r+1,R*b)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L])%p))%p;
				fr(i,l,r)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L]+c)%p))%p;
				l1[L]=1;l2[L]=0;
				continue;
			}
			fr(i,L+1,R-1)
			{
				s[i]=(s[i]+c*b)%p;
				l2[i]=(l2[i]+c)%p;
			}
			s[L]=s[R]=0;
			fr(i,L*b-b+1,l-1)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L])%p))%p;
			fr(i,l,L*b)s[L]=(s[L]+(v[i]=(v[i]*l1[L]+l2[L]+c)%p))%p;
			fr(i,R*b-b+1,r)s[R]=(s[R]+(v[i]=(v[i]*l1[R]+l2[R]+c)%p))%p;
			fr(i,r+1,R*b)s[R]=(s[R]+(v[i]=(v[i]*l1[R]+l2[R])%p))%p;
			l1[L]=l1[R]=1;l2[L]=l2[R]=0;
		}
		if(opt==3)
		{
			unsigned long long l=read(),r=read(),ans=0,L,R;
			L=(l+b-1)/b;R=(r+b-1)/b;
			if(L==R)
			{
				fr(i,l,r)ans=(ans+v[i]*l1[L]+l2[L])%p;
				printf("%lld\n",ans);
				continue;
			}
			fr(i,L+1,R-1)ans=(ans+s[i])%p;
			fr(i,L*b-b+1,L*b)v[i]=(v[i]*l1[L]+l2[L])%p;
			fr(i,R*b-b+1,R*b)v[i]=(v[i]*l1[R]+l2[R])%p;
			l1[L]=l1[R]=1;l2[L]=l2[R]=0;
			fr(i,l,L*b)ans=(ans+v[i])%p;
			fr(i,R*b-b+1,r)ans=(ans+v[i])%p;
			printf("%lld\n",ans);
		}
	}
	return 0;
}