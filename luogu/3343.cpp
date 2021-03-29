/**************************************************************
	File name: 3343.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/22/2018, 1:19:45 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define N 12
#define K 100
int n,m,a[N][N];
double f[1<<N][K];
int main()
{
	n=read();
	fr(i,1,m=read())
	{
		int u=read(),v=read();
		a[u][v]=a[v][u]=1;
	}
	fr(i,2,(1<<n)-1)if(i&1)
		for(int j=(i-1)&i;j;j=(j-1)&i)if(j&1)
		{
			int e=0;
			fr(k,1,n)if((1<<(k-1))&(i^j))fr(o,1,n)if((1<<(o-1))&j)
				e+=a[k][o];
			fr(k,0,m-e)
				f[i][k]+=1./(1+k+e)-f[j][k+e];
//			printf("%d %d %d\n",i,j,e);
		}
	printf("%.6lf\n",f[(1<<n)-1][0]);
	return 0;
}