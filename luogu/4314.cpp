/***************************************************************
	File name: 4314.cpp
	Author: huhao
	Create time: Sun 01 Sep 2019 10:01:56 AM CST
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
const int N=100010<<3;
const i64 inf=1ll<<50;
i64 n,q,m[N],h[N],p[N];
pair<i64,i64> M[N],H[N];
//x=max(max(x+a,b)+c,d)=max(x+a+c,b+c,d);
pair<i64,i64> mmerge(pair<i64,i64> a,pair<i64,i64> b)
{
	return make_pair(max(-inf,a.first+b.first),max(a.second+b.first,b.second));
}
//x=max(max(x+a,b),max(x+c,d))=max(x+max(a,c),max(b,d)));
pair<i64,i64> hmerge(pair<i64,i64> a,pair<i64,i64> b)
{
	return make_pair(max(a.first,b.first),max(a.second,b.second));
}
void modify(i64 k,pair<i64,i64> mm,pair<i64,i64> hh)
{
	H[k]=hmerge(mmerge(M[k],hh),H[k]);
	M[k]=mmerge(M[k],mm);
	h[k]=max(h[k],max(m[k]+hh.first,hh.second));
	m[k]=max(m[k]+mm.first,mm.second);
}
void pushdown(i64 k)
{
	if(!p[k])
	{
		modify(k<<1,M[k],H[k]);
		modify(k<<1|1,M[k],H[k]);
	}
	M[k]=H[k]=make_pair(0,-inf);
}
void update(i64 k)
{
	if(!p[k])
	{
		pushdown(k<<1);
		pushdown(k<<1|1);
		h[k]=max(h[k<<1],h[k<<1|1]);
		m[k]=max(m[k<<1],m[k<<1|1]);
	}
}
void build(i64 k,i64 l,i64 r)
{
	M[k].second=H[k].second=-inf;
	if(l==r)
	{
		m[k]=h[k]=read();
		p[k]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	update(k);
}
void modify(i64 k,i64 l,i64 r,i64 L,i64 R,pair<i64,i64> p)
{
	pushdown(k);
	if(l>R||r<L)
		return;
	if(L<=l&&r<=R)
	{
		modify(k,p,p);
		return;
	}
	i64 mid=(l+r)>>1;
	modify(k<<1,l,mid,L,R,p);
	modify(k<<1|1,mid+1,r,L,R,p);
	update(k);
}
i64 querym(i64 k,i64 l,i64 r,i64 L,i64 R)
{
	pushdown(k);
	if(l>R||r<L)
		return -inf;
	if(L<=l&&r<=R)
	{
		return m[k];
	}
	i64 mid=(l+r)>>1;
	return max(querym(k<<1,l,mid,L,R),querym(k<<1|1,mid+1,r,L,R));
}
i64 queryh(i64 k,i64 l,i64 r,i64 L,i64 R)
{
	pushdown(k);
	if(l>R||r<L)
		return -inf;
	if(L<=l&&r<=R)
	{
		return h[k];
	}
	i64 mid=(l+r)>>1;
	return max(queryh(k<<1,l,mid,L,R),queryh(k<<1|1,mid+1,r,L,R));
}
int main()
{
	n=read();
	build(1,1,n);
	q=read();
	while(q--)
	{
		char c[5];
		scanf("%s",c);
		if(*c=='P')
		{
			i64 l=read(),r=read();
			modify(1,1,n,l,r,make_pair(read(),-inf));
		}
		else if(*c=='C')
		{
			i64 l=read(),r=read();
			modify(1,1,n,l,r,make_pair(-inf,read()));
		}
		else if(*c=='Q')
		{
			i64 l=read(),r=read();
			printf("%lld\n",querym(1,1,n,l,r));
		}
		else
		{
			i64 l=read(),r=read();
			printf("%lld\n",queryh(1,1,n,l,r));
		}
	}
	return 0;
}
