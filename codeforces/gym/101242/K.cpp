/***************************************************************
	File name: K.cpp
	Author: huhao
	Create time: Thu 29 Oct 2020 08:20:28 AM CST
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
#include<bitset>
const int N=110,M=10110;
int n,a[M];
std::bitset<N> f[M][2];
inline bool query(int p,int l){ return a[p+l-1]-a[p-1]==l; }
int main()
{
	fr(i,1,read())
	{
		int A=read();
		fr(j,1,A) a[++n]=1;
		if(i!=end_i) a[++n]=0;
	}
	fr(i,1,n) a[i]+=a[i-1];
	if(a[n]==2){ printf("1\n"); return 0; }
	fd(t,n,2) if(query(1,t))
	{
		fr(i,1,n+1) fr(j,0,1) f[i][j].reset();
		f[t+1][0][t]=1;
		fr(i,t+1,n) fr(j,1,t) if(a[i]!=a[i-1])
		{
			if(j!=1)
			{
				if(f[i][1][j])
				{
					if(query(i,j)) f[i+j][0][j]=1;
					if(query(i,j+1)) f[i+(j+1)][1][j+1]=1;
				}
				if(f[i][0][j])
				{
					if(query(i,j-1)) f[i+(j-1)][0][j-1]=1;
				}
			}
			else
			{
				if(f[i][0][1]) f[i+1][1][1]=1;
				if(f[i][1][1])
				{
					f[i+1][0][1]=1;
					if(query(i,2)) f[i+2][1][2]=1;
				}
			}
		}
		else{ f[i+1][1][j]=f[i][1][j]; f[i+1][0][j]=f[i][0][j]; }
		if(f[n+1][1][t]){ printf("%d\n",t); return 0; }
	}
	printf("no quotation\n");
	return 0;
}
