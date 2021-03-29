/**************************************************************
	File name: 2178.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 3/4/2019, 8:11:32 PM
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
#define N 300010
#define inf (1ll<<60)
int n,sa[N],r[N],p[N],l[N],h[N],t[N],rh[N],st[N<<1][25],b[N];
long long a[N],a1[N],a2[N];
char s[N];
void _sort()
{
	int m=0;
	fr(i,1,n)
		m=max(m,r[i]);
	fr(i,1,m)
		t[i]=0;
	fr(i,1,n)
		t[r[i]]++;
	fr(i,1,m)
		t[i]+=t[i-1];
	fd(i,n,1)
		sa[t[r[p[i]]]--]=p[i];
}
int cmp1(int a,int b)
{
	return h[a]==h[b]?a<b:h[a]<h[b];
}
int q[N],x;
int getm(int l,int r)
{
	int k=b[r-l+1];
	return min(st[l][k],st[r-(1<<k)+1][k]);
}
void findm(int l,int r,int o)
{
	if(getm(l,r)!=o)
		return;
	int k=b[r-l+1];
	if(r==l)
	{
		q[++x]=l;
		return;
	}
	if((1<<k)==r-l+1)
	{
		findm(l,l+(1<<(k-1))-1,o);
		findm(l+(1<<(k-1)),r,o);
	}
	else
	{
		findm(l,l+(1<<k)-1,o);
		findm(l+(1<<k),r,o);
	}
}
void calc(int l,int r,long long &mi,long long &smi,long long &mx,long long &smx);
void query(int l,int r,int o,long long &mi,long long &smi,long long &mx,long long &smx)
{
	a1[getm(l,r)]+=(long long)(r-l+1)*(r-l+2)/2;
	a1[o]-=(long long)(r-l+1)*(r-l+2)/2;
	if(l>r)
	{
		if(mi>a[sa[r]])
		{
			smi=mi;
			mi=a[sa[r]];
		}
		else if(smi>a[sa[r]])
			smi=a[sa[r]];
		if(mx<a[sa[r]])
		{
			smx=mx;
			mx=a[sa[r]];
		}
		else if(smx<a[sa[r]])
			smx=a[sa[r]];
		return;
	}
	long long _mi,_smi,_mx,_smx;
	calc(l,r,_mi,_smi,_mx,_smx);
	long long a[4]={mi,smi,_mi,_smi};
	long long b[4]={mx,smx,_mx,_smx};
	sort(a,a+4);
	sort(b,b+4);
	mi=a[0];
	smi=a[1];
	mx=b[3];
	smx=b[2];
}
void calc(int l,int r,long long &mi,long long &smi,long long &mx,long long &smx)
{
	int o=getm(l,r);
	if(l==r)
	{
		mi=smx=min(a[sa[l-1]],a[sa[l]]);
		smi=mx=max(a[sa[l-1]],a[sa[l]]);
		a2[o]=max(a2[o],mx*smx);
		return;
	}
	mi=inf;
	smi=inf;
	mx=-inf;
	smx=-inf;
	int _l=x+1,_r;
	findm(l,r,o);
	_r=x;
	query(l,q[_l]-1,o,mi,smi,mx,smx);
	query(q[_r]+1,r,o,mi,smi,mx,smx);
	fr(i,_l,_r-1)
	{
		query(q[i]+1,q[i+1]-1,o,mi,smi,mx,smx);
	}
	a2[o]=max(a2[o],max(mi*smi,mx*smx));
}
int main()
{
	n=read();
	scanf("%s",s+1);
	fr(i,1,n)
		a[i]=read();
	fr(i,2,n)
		b[i]=b[i>>1]+1;
	fr(i,1,n)
	{
		r[i]=s[i]-'a'+1;
		p[i]=i;
	}
	_sort();
	fr(i,0,log2(n))
	{
		int c=0;
		fr(j,0,(1<<i)-1)
			p[++c]=n-j;
		fr(j,1,n)
			if(sa[j]>(1<<i))
				p[++c]=sa[j]-(1<<i);
		_sort();
		int m=1;
		fr(j,1,n)
			l[j]=r[j];
		r[sa[1]]=1;
		fr(j,2,n)
		{
			if(l[sa[j]]!=l[sa[j-1]]||l[sa[j]+(1<<i)]!=l[sa[j-1]+(1<<i)])
				m++;
			r[sa[j]]=m;
		}
		if(m==n)
			break;
	}
	int k=0;
	fr(i,1,n)
	{
		int j=sa[r[i]-1];
		if(k)
			k--;
		while(s[i+k]==s[j+k])
			k++;
		h[r[i]]=k;
	}
	fr(i,1,n)
		st[i][0]=h[i];
	fr(j,1,20)
		fr(i,1,n)
			if(i+(1<<(j-1))<=n)
				st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
	long long _a,_b,_c,_d;
	fr(i,0,n-1)
		a2[i]=-inf;
	findm(2,n,0);
	a1[0]=(long long)n*(n-1)/2;
	calc(2,n,_a,_b,_c,_d);
	fd(i,n-2,0)
		a2[i]=max(a2[i],a2[i+1]);
	fd(i,n-2,0)
		a1[i]+=a1[i+1];
	fr(i,0,n-1)
		printf("%lld %lld\n",a1[i],a2[i]==-inf?0:a2[i]);
	return 0;
}