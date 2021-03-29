/***************************************************************
	File name: 2463.cpp
	Author: huhao
	Create time: Wed 10 Jul 2019 08:02:28 PM CST
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
const int N=1010,M=2000010,L=20;
int n,a[N][N],m,s[M],b[M],sa[M],r[M],p[M],l[M],ans,c,t[M],_r[M],h[M][L+10],d[M];
void sort()
{
	fr(i,1,n)
		t[r[i]]++;
	fr(i,1,c)
		t[i]+=t[i-1];
	fd(i,n,1)
		sa[t[r[p[i]]]--]=p[i];
	fr(i,0,c)
		t[i]=0;
}
int lcp(int _l,int _r)
{
	_l=r[_l];
	_r=r[_r];
	if(_l>_r)
		swap(_l,_r);
	_l++;
	if(_l>_r)
		return 0;
	int k=log2(_r-_l+1);
	return min(h[_l][k],h[_r-(1<<k)+1][k]);
}
#include<stdlib.h>
int main()
{
	srand((unsigned long long)new char);
	m=read();
	ans=1;
	fr(i,1,m)
	{
		a[i][0]=read();
		fr(j,1,a[i][0])
			a[i][j]=read();
		fr(j,1,a[i][0]-1)
		{
			n++;
			r[n]=s[n]=a[i][j]-a[i][j+1]+10000;
			b[n]=i;
		}
		n++;
		r[n]=s[n]=rand()%5000+15000;
		b[n]=m+1;
	}
	fr(i,1,n)
	{
		p[i]=i;
		c=max(c,s[i]);
	}
	sort();
	fr(i,0,20)
	{
		p[0]=0;
		fr(j,1,(1<<i))
			p[++p[0]]=n-j+1;
		fr(j,1,n)
			if(sa[j]>(1<<i))
				p[++p[0]]=sa[j]-(1<<i);
		sort();
		c=1;
		fr(j,1,n)
			_r[j]=r[j];
		r[sa[1]]=1;
		fr(j,2,n)
		{
			if(_r[sa[j]]!=_r[sa[j-1]]||_r[sa[j]+(1<<i)]!=_r[sa[j-1]+(1<<i)])
				c++;
			r[sa[j]]=c;
		}
		if(c==n)
			break;
	}
	int _h=0;
	fr(i,1,n)
	{
		_h=max(_h-1,0);
		while(s[sa[r[i]]+_h]==s[sa[r[i]-1]+_h])
			_h++;
		h[r[i]][0]=_h;
	}
	fr(j,1,L)
		fr(i,1,n-(1<<j)+1)
			h[i][j]=min(h[i][j-1],h[i+(1<<(j-1))][j-1]);
	for(int i=1,j=0;j<=n;)
	{
		while(j<=n&&d[0]!=m)
		{
			j++;
			if(!d[b[sa[j]]]&&b[sa[j]]!=m+1)
				d[0]++;
			d[b[sa[j]]]++;
		}
		if(j>n)
			break;
		ans=max(ans,lcp(sa[i],sa[j]));
		d[b[sa[i]]]--;
		if(!d[b[sa[i]]]&&b[sa[i]]!=m+1)
			d[0]--;
		i++;
	}
	printf("%d\n",ans+1);
	return 0;
}
