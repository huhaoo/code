/***************************************************************
	File name: 3809.cpp
	Author: huhao
	Create time: Thu 11 Jul 2019 08:20:51 PM CST
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
const int N=2000010,L=20;
int n,sa[N],r[N],_r[N],h[N][L+10],t[N],p[N],m,l[N];
char s[N];
void sort()
{
	fr(i,1,n)
		t[r[i]]++;
	fr(i,1,m)
		t[i]+=t[i-1];
	fd(i,n,1)
		sa[t[r[p[i]]]--]=p[i];
	fr(i,0,m)
		t[i]=0;
}
int lcp(int a,int b)
{
	a=r[a];
	b=r[b];
	if(a<b)
		swap(a,b);
	a++;
	int k=l[b-a+1];
	return min(h[a][k],h[b-(1<<k)+1][k]);
}
int main()
{
	scanf("%s",s+1);
	n=strlen(s+1);
	m=256;
	fr(i,1,n)
	{
		r[i]=s[i];
		p[i]=i;
	}
	sort();
	fr(i,0,L)
	{
		p[0]=0;
		fr(j,1,(1<<i))
			p[++p[0]]=n-j+1;
		fr(j,1,n)
			if(sa[j]>(1<<i))
				p[++p[0]]=sa[j]-(1<<i);
		sort();
		fr(j,1,n)
			_r[j]=r[j];
		r[sa[1]]=m=1;
		fr(j,2,n)
		{
			if(_r[sa[j]]!=_r[sa[j-1]]||_r[sa[j]+(1<<i)]!=_r[sa[j-1]+(1<<i)])
				m++;
			r[sa[j]]=m;
		}
		if(m==n)
			break;
	}
	int k=0;
	fr(i,1,n)
	{
		k=max(k-1,0);
		while(s[i+k]==s[sa[r[i]-1]+k])
			k++;
		h[r[i]][0]=k;
	}
	fr(i,1,L)
		fr(j,1,n+1-(1<<i))
			h[i][j]=min(h[j][i-1],h[j+(1<<(i-1))+1][i-1]);
	fr(i,2,n)
		l[i]=l[i>>1]+1;
	fr(i,1,n)
		printf("%d%c",sa[i],i==n?'\n':' ');
	return 0;
}
