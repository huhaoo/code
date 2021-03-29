/***************************************************************
	File name: G.cpp
	Author: huhao
	Create time: Tue 17 Nov 2020 08:16:21 AM CST
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
#define i64 long long
const int N=30010;
int n,a[N],b[N],c[N],B[N],C[N],k,r;
int s[1<<18|10];
i64 ans;
int main()
{
	n=read(); r=read(); k=read();
	fr(i,1,n) a[i]=read();
	fr(i,1,n) B[i]=(b[i]=read())-a[i];
	fr(i,1,n) C[i]=(c[i]=read())-b[i];
	fr(i,1,n-r)
	{
		i64 v=0;
		fr(j,0,r-1) v+=B[i+j]+C[i+j];
		fr(j,i,n-r)
		{
			v+=-(j<=i+r-1?C[j]:B[j])+B[j+r];
			s[v>>18]++;
		}
	}
	fr(i,0,(1<<18)-1)
		if(k>s[i]) k-=s[i];
		else{ ans+=(i64)i<<18; break; }
	memset(s,0,sizeof(s));
	fr(i,1,n-r)
	{
		i64 v=0;
		fr(j,0,r-1) v+=B[i+j]+C[i+j];
		fr(j,i,n-r)
		{
			v+=-(j<=i+r-1?C[j]:B[j])+B[j+r];
			if((v-ans)>>18) ; else s[v&((1<<18)-1)]++;
		}
	}
	fr(i,0,(1<<18)-1)
		if(k>s[i]) k-=s[i];
		else{ ans+=(i64)i; break; }
	fr(i,1,n) ans+=a[i];
	printf("%lld\n",ans);
	return 0;
}
