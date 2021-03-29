/***************************************************************
	File name: 164.cpp
	Author: huhao
	Create time: Sun 01 Sep 2019 07:40:00 PM CST
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
#define pair pair<i64,i64>
const int N=500010<<2;
const i64 inf=1ll<<50;
i64 n,q,a[N];
pair t[N],h[N];
//t=t+T
//h=h*t
pair merget(pair a,pair b)
{
	return pair(max(a.first+b.first,-inf),max(a.second+b.first,b.second));
}
pair mergeh(pair a,pair b)
{
	return pair(max(a.first,b.first),max(a.second,b.second));
}
void pushdown(i64 k)
{
	h[k<<1]=mergeh(h[k<<1],merget(t[k<<1],h[k]));
	t[k<<1]=merget(t[k<<1],t[k]);
	h[k<<1|1]=mergeh(h[k<<1|1],merget(t[k<<1|1],h[k]));
	t[k<<1|1]=merget(t[k<<1|1],t[k]);
	t[k]=h[k]=pair(0,-inf);
}
void modify(i64 k,i64 l,i64 r,i64 L,i64 R,pair T)
{
	if(l>R||r<L)
		return;
	if(L<=l&&r<=R)
	{
//		printf("%lld %lld\n",l,r);
		t[k]=merget(t[k],T);
		h[k]=mergeh(h[k],t[k]);
		return;
	}
	pushdown(k);
	i64 mid=(l+r)>>1;
	modify(k<<1,l,mid,L,R,T);
	modify(k<<1|1,mid+1,r,L,R,T);
}
pair query(i64 k,i64 l,i64 r,i64 p,pair *a)
{
	if(l==r)
		return a[k];
//	printf("%lld %lld\n",l,r);
	pushdown(k);
	int mid=(l+r)>>1;
	if(p<=mid)
		return query(k<<1,l,mid,p,a);
	else
		return query(k<<1|1,mid+1,r,p,a);
}
void build(i64 k,i64 l,i64 r)
{
	t[k]=h[k]=pair(0,-inf);
	if(l==r)
		return;
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
}
int main()
{
	n=read();
	q=read();
	build(1,1,n);
	fr(i,1,n)
		a[i]=read();
	while(q--)
	{
		int opt=read();
		if(opt==1)
		{
			i64 l=read(),r=read(),v=read();
			modify(1,1,n,l,r,pair(v,-inf));
		}
		else if(opt==2)
		{
			i64 l=read(),r=read(),v=read();
			modify(1,1,n,l,r,pair(-v,0));
		}
		else if(opt==3)
		{
			i64 l=read(),r=read(),v=read();
			modify(1,1,n,l,r,pair(-inf,v));
		}
		else if(opt==4)
		{
			i64 p=read();
			pair ans=query(1,1,n,p,t);
//			printf("%lld %lld\n",ans.first,ans.second);
			printf("%lld\n",max(a[p]+ans.first,ans.second));
		}
		else
		{
			i64 p=read();
			pair ans=query(1,1,n,p,h);
//			printf("%lld %lld\n",ans.first,ans.second);
			printf("%lld\n",max(a[p]+ans.first,ans.second));
		}
	}
	return 0;
}
