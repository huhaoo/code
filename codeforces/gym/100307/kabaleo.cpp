/***************************************************************
	File name: kabaleo.cpp
	Author: huhao
	Create time: Sun 22 Nov 2020 05:06:09 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
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
#include<set>
const int N=1000010;
int n,m,c,h;
int b[N],l[N];
int s[N],w[N];
int mx,Mx;
int a[N],A;
int main()
{
	freopen("kabaleo.in","r",stdin); freopen("kabaleo.out","w",stdout);
	n=read(); m=read(); c=read(); h=read();
	fr(i,1,n) s[b[i]=read()]++;
	fr(i,1,m) l[i]=read();
	if(s[h]==n)
	{
		fr(i,1,m){ s[h]--; s[l[i]]++; }
		fr(i,1,m) if(i!=h&&s[i]>=s[h]){ printf("0\n"); return 0; }
		printf("%d\n",n);
		fr(i,1,n) printf("%d%c",i,i==n?'\n':' ');
		return 0;
	}
	fr(i,1,c) w[i]=s[i];
	w[l[1]]++;
	fr(i,2,m){ w[l[i]]++; w[h]--; }
	fr(i,1,c) if(i!=h)
	{
		if(w[i]>w[mx]){ Mx=mx; mx=i; }
		else if(w[i]>w[Mx]) Mx=i;
	}
	fr(i,1,n)
	{
		w[b[i]]--;
//		fr(i,1,c) printf("%d%c",w[i],i==c?'\n':' ');
		if(w[mx]<w[h]&&w[Mx]<w[h]) a[++A]=i;
		w[b[i]]++;
	}
	printf("%d\n",A);
	fr(i,1,A) printf("%d%c",a[i],i==A?'\n':' ');
	return 0;
}
