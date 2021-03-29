/***************************************************************
	File name: 2315.cpp
	Author: huhao
	Create time: Fri 24 May 2019 03:08:38 PM CST
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
const int N=1010;
int n,l[N][N],r[N][N],d[N][N],L[N][N],R[N][N],D[N][N],ans;
int main()
{
	n=read();
	fr(i,1,n)
		fr(j,1,i)
		{
			l[i][j]=read();
			r[i][j]=read();
			d[i][j]=read();
		}
	fd(i,n,1)
		fd(j,i,1)
		{
			if(l[i][j])
				L[i][j]=L[i+1][j]+1;
			if(r[i][j])
				R[i][j]=R[i+1][j+1]+1;
			if(d[i][j])
				D[i][j]=D[i][j+1]+1;
		}
	fr(i,1,n)
		fr(j,1,i)
			fr(k,1,min(L[i][j],R[i][j]))
				if(D[i+k-1][j]>=k)
					ans++;
	fr(i,1,n)
		fr(j,1,i)
			fr(k,1,min(D[i-1][j],R[i][j]))
				if(L[i][j+k]>=k)
					ans++;
	printf("%d\n",ans);
	return 0;
}
