/***************************************************************
	File name: landscape.cpp
	Author: huhao
	Create time: Sat 31 Oct 2020 11:07:38 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
i64 read()
{
	i64 r=0,t=1,c=getchar();
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
const int N=1<<18|10;
int n; i64 m; int a[N]; i64 s[N];
int m1[N],m2[N];
void build(int k,int l,int r)
{
	if(l==r){ m1[k]=a[l]-l; m2[k]=a[l]+l; return ; }
	int mid=(l+r)>>1;
	build(k<<1,l,mid); build(k<<1|1,mid+1,r);
	m1[k]=std::max(m1[k<<1],m1[k<<1|1]); m2[k]=std::max(m2[k<<1],m2[k<<1|1]);
}
int query1(int k,int l,int r,int p,int v)
{
	if(l>p||m1[k]<v) return -1;
	if(l==r) return l;
	int mid=(l+r)>>1;
	int q=query1(k<<1|1,mid+1,r,p,v);
	if(q==-1) return query1(k<<1,l,mid,p,v);
	else return q;
}
int query2(int k,int l,int r,int p,int v)
{
	if(r<p||m2[k]<v) return -1;
	if(l==r) return l;
	int mid=(l+r)>>1;
	int q=query2(k<<1,l,mid,p,v);
	if(q==-1) return query2(k<<1|1,mid+1,r,p,v);
	else return q;
}
i64 sum(i64 a,i64 b){ return (a+b)*(b-a+1)/2; }
int check(int p,int h)
{
	int l=query1(1,1,n,p-1,h-p),r=query2(1,1,n,p+1,h+p);
	if(l==-1) return 0;
	if(r==-1) return 0;
	i64 _m=m+s[std::min(r,n)]-s[std::max(0,l-1)];
	_m-=h; _m-=sum(h-(p-l),h-1); _m-=sum(h-(r-p),h-1);
//	printf("%d %d   %d %d  %lld\n",p,h,l,r,_m);
	return _m>=0;
}
int check(int p){ fr(i,1,n) if(check(i,p)) return 1; return 0; }
int main()
{
	freopen("landscape.in","r",stdin); freopen("landscape.out","w",stdout);
	n=read(); m=read();
	fr(i,1,n) s[i]=s[i-1]+(a[i]=read());
	build(1,1,n);
	int l=1,r=2000000000;
	while(l<r)
	{
		int mid=((unsigned)l+r)>>1;
		if(check(mid)) l=mid+1;
		else r=mid;
	}
	int ans=l-1;
	fr(i,1,n) ans=std::max(ans,a[i]);
	printf("%d\n",ans);
	return 0;
}
