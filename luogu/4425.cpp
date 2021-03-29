/**************************************************************
	File name: 4425.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 12/16/2018, 3:40:17 PM
**************************************************************/
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
#define N 400010
#define inf 536870911
int n,m,q,ans,a[N],t[N],s[N];
int query(int k,int l,int r,int v)
{
	if(l==r)return t[k]>v?v+l:inf;
	int mid=(l+r)>>1;
	if(t[k<<1|1]>v)return min(s[k],query(k<<1|1,mid+1,r,v));
	else return query(k<<1,l,mid,v);
}
void update(int k,int l,int mid)
{
	t[k]=max(t[k<<1],t[k<<1|1]);
	s[k]=query(k<<1,l,mid,t[k<<1|1]);
}
void build(int k,int l,int r)
{
	if(l==r)
	{
		t[k]=a[l]-l;
		return;
	}
	int mid=(l+r)>>1;
	build(k<<1,l,mid);
	build(k<<1|1,mid+1,r);
	update(k,l,mid);
}
void modfiy(int k,int l,int r,int x,int y)
{
	if(l==r)
	{
		t[k]=y-l;
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)modfiy(k<<1,l,mid,x,y);
	else modfiy(k<<1|1,mid+1,r,x,y);
	update(k,l,mid);
}
int main()
{
	n=read();m=read();q=read();
	fr(i,1,n)a[i]=read();
	build(1,1,n);
	printf("%d\n",ans=query(1,1,n,t[1]-n)+n);
	while(m--)
	{
		int x=read()^(q*ans),y=read()^(q*ans);
		modfiy(1,1,n,x,y);
		printf("%d\n",ans=query(1,1,n,t[1]-n)+n);
	}
	return 0;
}