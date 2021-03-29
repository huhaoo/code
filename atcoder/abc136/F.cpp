/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Sun 04 Aug 2019 08:44:28 PM CST
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
const i64 N=200010,mod=998244353;
i64 x[N],y[N],a[N],n,b[N],c[N],p2[N],_y[N],ans;
void add(i64 *b,i64 p,i64 v)
{
	while(p)
	{
		b[p]+=v;
		p-=p&(-p);
	}
}
i64 query(i64 *b,i64 p)
{
	i64 r=0;
	while(p<=n)
	{
		r+=b[p];
		p+=p&(-p);
	}
	return r;
}
i64 query(i64 *b,i64 l,i64 r)
{
	return (query(b,l)-query(b,r+1)+mod)%mod;
}
int main()
{
	n=read();
	fr(i,1,n)
	{
		x[i]=read();
		y[i]=read();
		a[i]=x[i];
	}
	sort(a+1,a+n+1);
	fr(i,1,n)
		x[i]=lower_bound(a+1,a+n+1,x[i])-a;
	fr(i,1,n)
		a[i]=y[i];
	sort(a+1,a+n+1);
	fr(i,1,n)
		y[i]=lower_bound(a+1,a+n+1,y[i])-a;
	fr(i,1,n)
		_y[x[i]]=y[i];
	fr(i,1,n)
		y[i]=_y[i];
	p2[0]=1;
	fr(i,1,n)
		p2[i]=p2[i-1]*2%mod;
	fr(i,1,n)
		add(c,y[i],1);
	fr(i,0,n)
		p2[i]=(p2[i]-1+mod)%mod;
	fr(i,1,n)
	{
		ans=(ans+p2[n]-p2[i-1]-p2[n-i]-p2[y[i]-1]-p2[n-y[i]]+4ll*mod)%mod;
		add(c,y[i],-1);
		ans=(ans+p2[query(c,1,y[i]-1)]+p2[query(c,y[i]+1,n)]+p2[query(b,1,y[i]-1)]+p2[query(b,y[i]+1,n)])%mod;
		add(b,y[i],1);
	}
	printf("%lld\n",ans);
	return 0;
}
