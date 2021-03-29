/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Wed 14 Oct 2020 11:19:50 AM CST
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
const int N=25,M=1<<20|10;
int n,m,a[M],b[M],c[M],f[M],g[M],A[M],B[M];
int s1[N*M],s2[N*M],c1,c2,s;
void fwt(int *a,int n){ fr(i,0,n-1) for(int j=0;j<(1<<n);j+=(1<<(i+1))) fr(k,0,(1<<i)-1) a[(1<<i)+j+k]+=a[j+k]; }
long long ans;
int main()
{
	n=read(); m=read();
	fr(i,0,n-1)
	{
		static char s[N];
		scanf("%s",s);
		fr(j,0,m-1) if(s[j]=='1'){ a[1<<i]|=1<<j; b[1<<j]|=1<<i; }
	}
	fr(i,0,n-1) A[1<<i]=read();
	fr(i,0,m-1) B[1<<i]=read();
	fr(i,1,(1<<n)-1) A[i]=A[i&(i-1)]+A[i&(-i)];
	fr(i,1,(1<<m)-1) B[i]=B[i&(i-1)]+B[i&(-i)];
//	fr(i,0,(1<<n)-1) printf("%d%c",A[i],i==end_i?'\n':' ');
//	fr(i,0,(1<<m)-1) printf("%d%c",B[i],i==end_i?'\n':' ');
	s=read();
	fr(i,1,(1<<20)-1) c[i]=c[i&(i-1)]+1;
	fr(i,1,(1<<n)-1) a[i]=a[i&(i-1)]|a[i&(-i)];
	fr(i,1,(1<<m)-1) b[i]=b[i&(i-1)]|b[i&(-i)];
	fr(i,0,(1<<n)-1) a[i]=(c[a[i]]>=c[i]);
	fr(i,0,(1<<m)-1) b[i]=(c[b[i]]>=c[i]);
	fwt(a,n); fwt(b,m);
	fr(i,0,(1<<n)-1) a[i]=(a[i]>=(1<<c[i]));
	fr(i,0,(1<<m)-1) b[i]=(b[i]>=(1<<c[i]));
	fr(i,0,(1<<n)-1) if(a[i]) s1[++c1]=A[i];
	fr(i,0,(1<<m)-1) if(b[i]) s2[++c2]=B[i];
	std::sort(s1+1,s1+c1+1); std::sort(s2+1,s2+c2+1);
//	fr(i,1,c1) printf("%d%c",s1[i],i==c1?'\n':' ');
//	fr(i,1,c2) printf("%d%c",s2[i],i==c2?'\n':' ');
	for(int i=1,j=c2;i<=c1;i++)
	{
		while(j&&s1[i]+s2[j]>=s) j--;
		ans+=c2-j;
	}
	printf("%lld\n",ans);
	return 0;
}
