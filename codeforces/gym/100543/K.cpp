/***************************************************************
	File name: K.cpp
	Author: huhao
	Create time: Sun 03 Jan 2021 04:50:35 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
#define pii std::pair<int,int>
const int N=150010,K=15;
int n,k;
pii a[N];
int f[N][K];
int main()
{
	fr(T,1,read())
	{
		n=read(); k=read();
		fr(i,1,n){ a[i].first=read(); a[i].second=read(); }
		std::sort(a+1,a+n+1);
		fr(i,0,n+1) fr(j,0,k+1) f[i][j]=0;
		fd(i,n,1) fr(j,0,k)
		{
			f[i][j]=f[i+1][j];
			if(j) f[i][j]=std::max(f[i][j],std::min(a[i].first-a[i].second,f[i+1][j-1]-a[i].second));
			else f[i][j]=std::max(f[i][j],a[i].first-a[i].second);
		}
		printf("%d\n",f[1][k]);
//		fr(i,1,n) fr(j,0,k) printf("%d%c",f[i][j],j==k?'\n':' ');
	}
	return 0;
}
