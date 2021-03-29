/***************************************************************
	File name: 4887.cpp
	Author: huhao
	Create time: Thu 24 Oct 2019 03:46:34 PM CST
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
const int N=200010,W=400,M=16383;
int n,q,k,a[N],C,l,r,Q,c[N];
long long ans[N],pre[N],t[N];
struct query1
{
	int l,r,id;
}q1[N];
struct query2
{
	int id,p,l,r,op;
	query2(int I=0,int P=0,int L=0,int R=0,int O=0)
	{
		id=I;
		p=P;
		l=L;
		r=R;
		op=O;
	}
}q2[N];
int operator<(query1 a,query1 b)
{
	return
		a.l/W!=b.l/W?a.l<b.l:
		             a.r<b.r;
}
int operator<(query2 a,query2 b)
{
	return a.p<b.p;
}
int count(int k)
{
	return k?1+count(k&(k-1)):0;
}
int main()
{
	n=read();
	q=read();
	k=read();
	fr(i,0,M)
		if(count(i)==k)
			a[++C]=i;
	fr(i,1,n)
	{
		c[i]=read();
		fr(j,1,C)
			pre[i]+=t[c[i]^a[j]];
		t[c[i]]++;
		pre[i]+=pre[i-1];
	}
	int _k=0;
	fr(i,1,k)
		_k=_k<<1|1;
	fr(i,1,q)
	{
		q1[i].l=read();
		q1[i].r=read();
		q1[i].id=i;
		if(_k>M)
			printf("0\n");
	}
	if(_k>M)
		return 0;
	fr(i,0,M)
		t[i]=0;
	sort(q1+1,q1+q+1);
	l=1;
	r=0;
	fr(i,1,q)
	{
		if(l>q1[i].l)
		{
			q2[++Q]=query2(q1[i].id,r,q1[i].l,l-1,1);
			ans[q1[i].id]-=pre[l-1]-pre[q1[i].l-1];
			l=q1[i].l;
		}
		if(r<q1[i].r)
		{
			q2[++Q]=query2(q1[i].id,l-1,r+1,q1[i].r,-1);
			ans[q1[i].id]+=pre[q1[i].r]-pre[r];
			r=q1[i].r;
		}
		if(l<q1[i].l)
		{
			q2[++Q]=query2(q1[i].id,r,l,q1[i].l-1,-1);
			ans[q1[i].id]+=pre[q1[i].l-1]-pre[l-1];
			l=q1[i].l;
		}
		if(r>q1[i].r)
		{
			q2[++Q]=query2(q1[i].id,l-1,q1[i].r+1,r,1);
			ans[q1[i].id]-=pre[r]-pre[q1[i].r];
			r=q1[i].r;
		}
	}
//	fr(i,1,q)
//		printf("%d%c",ans[i],i==q?'\n':' ');
	sort(q2+1,q2+Q+1);
//	fr(i,1,Q)
//		printf("%d %d %d %d %d\n",q2[i].id,q2[i].p,q2[i].l,q2[i].r,q2[i].op);
	int j=1;
	while(j<=Q&&q2[j].p==0)
		j++;
	fr(i,1,n)
	{
		fr(k,1,C)
			t[c[i]^a[k]]++;
		while(j<=Q&&q2[j].p==i)
		{
			fr(k,q2[j].l,q2[j].r)
			{
				if(::k==0&&k<=i)
					ans[q2[j].id]-=q2[j].op;
				ans[q2[j].id]+=q2[j].op*t[c[k]];
			}
			j++;
		}
	}
	fr(i,1,q)
		ans[q1[i].id]+=ans[q1[i-1].id];
	fr(i,1,q)
		printf("%lld\n",ans[i]);
	return 0;
}
