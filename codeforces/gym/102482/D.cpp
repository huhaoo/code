/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Wed 14 Oct 2020 08:57:10 PM CST
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
#define f80 long double
const int N=1010;
int n,d,r;
f80 C[N][N],g[N][N],rC[N][N];
f80 ans;
int main()
{
	n=read(); d=read(); r=read();
	fr(i,0,n+d)
	{
		C[i][i]=C[i][0]=1;
		fr(j,1,i-1) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	fr(i,0,n+d) fr(j,0,i) rC[j][i]=C[i][j];
	fr(i,1,d)
	{
		memset(g,0,sizeof(g));
		g[0][0]=1;
		fr(j,1,n)
		{
			static double s[N];
			s[0]=g[j-1][0];
			fr(k,1,d) s[k]=s[k-1]+g[j-1][k];
			fr(k,0,d)
			{
				g[j][k]=s[k];
				if(k>=i) g[j][k]-=s[k-i];
			}
		}
		fr(j,1,std::min(d/i,r)) fr(k,j,n)
		{
			f80 Ans=0;
			fr(l,0,d-j*i) Ans+=g[k-j][l]*rC[n-1-(k-j)][n-1-(k-j)+d-j*i-l];
			ans+=C[k-1][j-1]*Ans;
		}
	}
	printf("%.10lf\n",(double)(ans/C[n+d-1][n-1]+r));
	return 0;
}
