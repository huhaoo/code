/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Thu 17 Jun 2021 02:26:59 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define i64 long long
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
const int N=200010;
int n,a[N],b[N],c[N],l[N],r[N],v[N];
int solve()
{
	n=read();
	fr(i,1,n)
	{
		a[i]=read(); b[i]=read(); c[i]=read();
		if(a[i]>=i) l[i]=-i;
		else if(a[i]+b[i]>=i) l[i]=-a[i];
		else l[i]=-a[i]+(i-a[i]-b[i]);
		if(c[i]>=i) r[i]=i;
		else if(c[i]+b[i]>=i) r[i]=c[i];
		else r[i]=c[i]-(i-c[i]-b[i]);
	}
//	fr(i,1,n) printf("%d %d\n",l[i],r[i]);
	fr(i,1,n)
	{
		if(!b[i]&&(l[i]-i)%2!=0) l[i]++;
		if(!b[i]&&(r[i]-i)%2!=0) r[i]--;
		l[i+1]=std::max(l[i+1],l[i]-1); r[i+1]=std::min(r[i+1],r[i]+1);
	}
	fd(i,n,1)
	{
		if(!b[i]&&(l[i]-i)%2!=0) l[i]++;
		if(!b[i]&&(r[i]-i)%2!=0) r[i]--;
		l[i-1]=std::max(l[i-1],l[i]-1); r[i-1]=std::min(r[i-1],r[i]+1);
	}
//	fr(i,1,n) printf("%d %d\n",l[i],r[i]);
	fr(i,1,n) if(l[i]>r[i]) return 0;
	int p=1;
	fr(i,1,n) if(l[i]>l[p]) p=i;
	v[p]=l[p]; int mx=v[p];
	if(std::max(0,v[p])+std::max(c[p]-a[p]-v[p],0)>c[p]) return 0;
	fd(i,p-1,1)
	{
		v[i]=std::min({r[i],v[i+1]+1,mx});
		if(!b[i]&&(v[i]-i)%2!=0) v[i]--;
		if(v[i]<v[i+1]-1||v[i]<l[i]) return 0;
		mx=std::min(mx,c[i]-(std::max(v[p],c[i]-a[i])-v[i]));
		if(v[i]>mx||0>mx) return 0;
	}
	mx=v[p];
	fr(i,p+1,n)
	{
		v[i]=std::min({r[i],v[i-1]+1,mx});
		if(!b[i]&&(v[i]-i)%2!=0) v[i]--;
		if(v[i]<v[i-1]-1||v[i]<l[i]) return 0;
		mx=std::min(mx,c[i]-(v[p]-v[i]));
//		printf("%d %d\n",mx,v[p]);
		if(v[i]>mx||c[i]-a[i]>c[i]-(v[p]-v[i])) return 0;
	}
	fr(i,1,n) if(c[i]-a[i]<v[n]) return 0;
//	fr(i,1,n) printf("%d%c",v[i],i==n?'\n':' ');
	return 1;
}
int main()
{
	fr(T,1,read()) printf("%s\n",solve()?"Yes":"No");
	return 0;
}
