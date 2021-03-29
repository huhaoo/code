/***************************************************************
	File name: hdu5306.cpp
	Author: huhao
	Create time: Fri 30 Aug 2019 04:45:02 PM CST
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
const int N=1000010<<3;
i64 n,m1[N],m2[N],mc[N],q,a[N],s[N];
void update(i64 k)
{
	if(m1[k<<1]==m1[k<<1|1])
	{
		mc[k]=mc[k<<1]+mc[k<<1|1];
		m1[k]=m1[k<<1];
		m2[k]=max(m2[k<<1],m2[k<<1|1]);
	}
	else if(m1[k<<1]<m1[k<<1|1])
	{
		m1[k]=m1[k<<1|1];
		mc[k]=mc[k<<1|1];
		m2[k]=max(m2[k<<1|1],m1[k<<1]);
	}
	else
	{
		m1[k]=m1[k<<1];
		mc[k]=mc[k<<1];
		m2[k]=max(m2[k<<1],m1[k<<1|1]);
	}
	s[k]=s[k<<1]+s[k<<1|1];
}
void pushdown(i64 k)
{
	if(k!=1&&m1[k]>m1[k>>1])
	{
		s[k]-=(m1[k]-m1[k>>1])*mc[k];
		m1[k]=m1[k>>1];
	}
}
void build(i64 k,i64 l,i64 r)
{
	if(l==r)
	{
		m1[k]=s[k]=a[l];
		mc[k]=1;
		m2[k]=0;
		m1[k<<1]=m1[k<<1|1]=m2[k<<1]=m2[k<<1|1]=mc[k<<1]=mc[k<<1|1]=0;
		return;
	}
	i64 mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	update(k);
}
void modify(i64 k,i64 v)
{
	pushdown(k);
	if(v>=m1[k])
		return;
	if(v>m2[k])
	{
		s[k]-=(m1[k]-v)*mc[k];
		m1[k]=v;
	}
	else
	{
		modify(k<<1,v);
		modify(k<<1|1,v);
		update(k);
	}
}
void modify(i64 k,i64 l,i64 r,i64 L,i64 R,i64 v)
{
	pushdown(k);
	if(l>R||r<L)
		return;
	if(L<=l&&r<=R)
	{
		modify(k,v);
		return;
	}
	i64 mid=(l+r)>>1;
	modify(k<<1,l,mid,L,R,v);
	modify(k<<1|1,mid+1,r,L,R,v);
	update(k);
}
i64 qmax(i64 k,i64 l,i64 r,i64 L,i64 R)
{
	pushdown(k);
	if(l>R||r<L)
		return -1;
	if(L<=l&&r<=R)
		return m1[k];
	i64 mid=(l+r)>>1;
	return max(qmax(k<<1,l,mid,L,R),qmax(k<<1|1,mid+1,r,L,R));
}
i64 qsum(i64 k,i64 l,i64 r,i64 L,i64 R)
{
	pushdown(k);
	if(l>R||r<L)
		return 0;
	if(L<=l&&r<=R)
		return s[k];
	i64 mid=(l+r)>>1;
	return qsum(k<<1,l,mid,L,R)+qsum(k<<1|1,mid+1,r,L,R);
}
int main()
{
	fr(T,1,read())
	{
		n=read();
		q=read();
		fr(i,1,n)
			a[i]=read();
		build(1,1,n);
		while(q--)
		{
			i64 opt=read();
			if(opt==0)
			{
				i64 l=read(),r=read(),v=read();
				modify(1,1,n,l,r,v);
			}
			else if(opt==1)
			{
				i64 l=read(),r=read();
				printf("%lld\n",qmax(1,1,n,l,r));
			}
			else
			{
				i64 l=read(),r=read();
				printf("%lld\n",qsum(1,1,n,l,r));
			}
		}
	}
	return 0;
}
