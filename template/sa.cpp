/***************************************************************
	File name: sa.cpp
	Author: huhao
	Create time: Sat 15 Aug 2020 12:25:41 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=(1<<21)|10;
int rk[N],sa[N],n,m,t[N],p[N],h[N];
char s[N];
void Sort()
{
	fr(i,1,m) t[i]=0;
	fr(i,1,n) t[rk[i]]++;
	fr(i,2,m) t[i]+=t[i-1];
	fd(i,n,1) sa[t[rk[p[i]]]--]=p[i];
}
int main()
{
	scanf("%s",s+1); n=strlen(s+1);
	fr(i,1,n){ rk[i]=s[i]-'a'+1; p[i]=i; }
	m=26;
	Sort();
	fr(i,0,20)
	{
		int c=0;
		fr(j,1,(1<<i)) p[++c]=n-j+1;
		fr(j,1,n) if(sa[j]>(1<<i)) p[++c]=sa[j]-(1<<i);
		Sort();
		static int r[N];
		fr(j,1,n) r[j]=rk[j];
		rk[sa[1]]=m=1;
		fr(j,2,n)
		{
			if(r[sa[j]]!=r[sa[j-1]]||r[sa[j]+(1<<i)]!=r[sa[j-1]+(1<<i)]) m++;
			rk[sa[j]]=m;
		}
		if(m==n) break;
	}
	fr(i,1,n) printf("%d%c",sa[i],i==n?'\n':' ');
	fr(i,1,n)
	{
		h[rk[i]]=std::max(0,h[rk[i-1]]-1);
		while(s[sa[rk[i]]+h[rk[i]]]==s[sa[rk[i]-1]+h[rk[i]]]) h[rk[i]]++;
	}
	fr(i,2,n) printf("%d%c",h[i],i==n?'\n':' ');
	return 0;
}
