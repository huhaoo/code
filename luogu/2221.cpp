/**************************************************************
	File name: 2221.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/21/2018, 12:41:32 PM
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
#define N 5000010
long long n,q,s[N][2],a[N],v0[N],v1[N],v2[N],s1[N],s2[N],r,c;
long long build(long long l,long long r)
{
	long long k=++c;
	if(l==r)return k;
	long long m=(l+r)>>1;
	s[k][0]=build(l,m);
	s[k][1]=build(m+1,r);
	return k;
}
void pushdown(long long k,long long l,long long r)
{
	if(a[k])
	{
		v0[k]+=(r-l+1)*a[k];
		v1[k]+=(s1[r]-s1[l-1])*a[k];
		v2[k]+=(s2[r]-s2[l-1])*a[k];
		a[s[k][0]]+=a[k];a[s[k][1]]+=a[k];
		a[k]=a[0]=0;
	}
}
void update(long long k,long long l,long long r)
{
	if(l==r)return;
	int m=(l+r)>>1;
	pushdown(s[k][0],l,m);pushdown(s[k][1],m+1,r);
	v0[k]=v0[s[k][0]]+v0[s[k][1]];
	v1[k]=v1[s[k][0]]+v1[s[k][1]];
	v2[k]=v2[s[k][0]]+v2[s[k][1]];
}
void add(long long k,long long l,long long r,long long ll,long long rr,long long v)
{
	if(ll<=l&&r<=rr)
	{
		a[k]+=v;
		return;
	}
	pushdown(k,l,r);
	long long m=(l+r)>>1;
	if(ll<=m)add(s[k][0],l,m,ll,rr,v);
	if(rr>m)add(s[k][1],m+1,r,ll,rr,v);
	update(k,l,r);
//	printf("%lld %lld %lld %lld %lld %lld\n",k,l,r,v0[k],v1[k],v2[k]);
}
long long query(long long k,long long l,long long r,long long ll,long long rr)
{
	update(k,l,r);pushdown(k,l,r);
	if(ll<=l&&r<=rr)
		return -v2[k]+(ll+rr)*v1[k]+(rr+1)*(1-ll)*v0[k];
	long long m=(l+r)>>1,ans=0;
	if(ll<=m)ans+=query(s[k][0],l,m,ll,rr);
	if(rr>m)ans+=query(s[k][1],m+1,r,ll,rr);
	return ans;
}
long long gcd(long long a,long long b)
{
	return b?gcd(b,a%b):a;
}
void print(long long k,long long l,long long r)
{
	if(!k)return;
//	printf("%lld %lld %lld %lld %lld ",l,r,v0[k],v1[k],v2[k]);
//	printf("%lld\n",a[k]);
	update(k,l,r);pushdown(k,l,r);
	printf("%lld %lld %lld %lld %lld\n",l,r,v0[k],v1[k],v2[k]);
	int m=(l+r)>>1;
	print(s[k][0],l,m);print(s[k][1],m+1,r);
}
int main()
{
	n=read();q=read();
	fr(i,1,n)s1[i]=s1[i-1]+i,s2[i]=s2[i-1]+i*i;
	r=build(1,n);
	while(q--)
	{
		char opt[10];
		scanf("%s",opt);
		if(*opt=='C')
		{
			long long ll=read(),rr=read()-1,v=read();
			add(r,1,n,ll,rr,v);
//			print(r,1,n);
		}
		else
		{
			long long ll=read(),rr=read()-1;
			long long a=query(r,1,n,ll,rr),b=(rr-ll+1)*(rr-ll+2)/2,g;
			g=gcd(a,b);a/=g;b/=g;
			printf("%lld/%lld\n",a,b);
		}
	}
	return 0;
}