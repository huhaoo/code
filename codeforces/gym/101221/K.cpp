/***************************************************************
	File name: K.cpp
	Author: huhao
	Create time: Tue 17 Nov 2020 09:57:52 AM CST
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
const int N=1000010,L=20;
int n,m,a[N],b[N],f[N][L+2];
inline void Max(int &a,int b){ if(a<b) a=b; }
int main()
{
	n=read(); m=read();
	fr(i,1,n+1) f[i][0]=i;
	fr(i,1,m){ a[i]=read(); b[i]=read(); if(a[i]<=b[i]) Max(f[a[i]][0],b[i]+1); else Max(f[1][0],b[i]+1); }
	fr(i,1,n) Max(f[i][0],f[i-1][0]);
	fr(j,1,L) fr(i,1,n+1) f[i][j]=f[f[i][j-1]][j-1];
	int ans=N;
	m++; a[m]=n+1; b[m]=0;
	fr(i,1,m) if(a[i]==b[i]+1||a[i]==1&&b[i]==n) ans=1;
	fr(i,1,m) if(a[i]>b[i])
	{
		int s=0,p=b[i]+1;
		fd(j,L,0) if(f[p][j]<a[i]){ s+=1<<j; p=f[p][j]; }
//		printf("%d %d   %d %d   %d\n",a[i],b[i],p,s,f[p][0]);
		if(f[p][0]>=a[i]) ans=std::min(ans,s+1+(i!=m));
	}
	if(ans==N) printf("impossible\n");
	else printf("%d\n",ans);
	return 0;
}
