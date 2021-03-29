/***************************************************************
	File name: improvements.cpp
	Author: huhao
	Create time: Fri 13 Nov 2020 09:19:25 PM CST
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
const int N=200010;
int n,p[N],ans,b[N],f[N],g[N];
int main()
{
	freopen("improvements.in","r",stdin); freopen("improvements.out","w",stdout);
	n=read();
	if(n<=2){ printf("%d\n",n); return 0; }
	fr(i,1,n) p[read()]=n-i+1;
	memset(b,0,sizeof(b));
	fr(i,1,n)
	{
		for(int j=p[i];j<=n;j+=j&(-j)) f[i]=std::max(f[i],b[j]);
		f[i]++;
		for(int j=p[i];j;j-=j&(-j)) b[j]=std::max(b[j],f[i]);
	}
	memset(b,0,sizeof(b));
	fd(i,n,1)
	{
		for(int j=p[i];j<=n;j+=j&(-j)) g[i]=std::max(g[i],b[j]);
		g[i]++;
		for(int j=p[i];j;j-=j&(-j)) b[j]=std::max(b[j],g[i]);
	}
/*	fr(i,1,n) printf("%d%c",p[i],i==n?'\n':' ');
	fr(i,1,n) printf("%d%c",f[i],i==n?'\n':' ');
	fr(i,1,n) printf("%d%c",g[i],i==n?'\n':' ');*/
	fr(i,1,n) ans=std::max(ans,f[i]+g[i]-1);
	printf("%d\n",ans);
	return 0;
}
