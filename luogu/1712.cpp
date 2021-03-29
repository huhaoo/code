/***************************************************************
	File name: 1712.cpp
	Author: huhao
	Create time: Wed 29 May 2019 04:30:14 PM CST
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
#include<map>
const int N=4000010;
map<int,int>t;
int n,m,a[N],ans=int(1e9)+10,v[N],w[N],_n;
struct line
{
	int l,r,w;
	line(int _l=0,int _r=0,int _w=0)
	{
		l=_l;
		r=_r;
		w=_w;
	}
}b[N];
int cmp(line a,line b)
{
	return a.w<b.w;
}
void add(int k,int l,int r,int pl,int pr,int _v)
{
	if(l>=pl&&r<=pr)
	{
		v[k]+=_v;
		return;
	}
	int mid=(l+r)>>1;
	if(mid>=pl)
		add(k<<1,l,mid,pl,pr,_v);
	if(mid<pr)
		add(k<<1|1,mid+1,r,pl,pr,_v);
	w[k]=max(w[k<<1]+v[k<<1],w[k<<1|1]+v[k<<1|1]);
}
int main()
{
	n=read();
	m=read();
	fr(i,1,n)
	{
		b[i].l=read();
		b[i].r=read();
		b[i].w=b[i].r-b[i].l;
		a[i*2-1]=b[i].l;
		a[i*2]=b[i].r;
	}
	sort(a+1,a+n*2+1);
	a[0]=-1;
	fr(i,1,n*2)
		if(a[i]!=a[i-1])
			t[a[i]]=++_n;
	fr(i,1,n)
	{
		b[i].l=t[b[i].l];
		b[i].r=t[b[i].r];
	}
	sort(b+1,b+n+1,cmp);
	int i=1,j=0;
	while(j<=n)
	{
		while(w[1]+v[1]<m)
		{
			if(j<n)
				j++;
			else
			{
				printf("%d\n",ans==int(1e9)+10?-1:ans);
				return 0;
			}
			add(1,1,_n,b[j].l,b[j].r,1);
		}
		ans=min(ans,b[j].w-b[i].w);
		add(1,1,_n,b[i].l,b[i].r,-1);
		i++;
	}
	printf("%d\n",ans==int(1e9)+10?-1:ans);
	return 0;
}
