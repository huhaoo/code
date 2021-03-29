/***************************************************************
	File name: L.cpp
	Author: huhao
	Create time: Fri 30 Oct 2020 05:05:18 PM CST
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
const int N=310,inf=1<<25;
int n,l[N],r[N],h[N],R[N],m;
int f[N][N];
int main()
{
	fr(T,1,read())
	{
		n=read(); m=0;
		fr(i,1,n){ l[i]=read(); r[i]=read(); h[i]=read(); R[++m]=r[i]; }
		std::sort(R+1,R+m+1); m=std::unique(R+1,R+m+1)-R-1;
		fr(i,1,n){ l[i]=std::lower_bound(R+1,R+m+1,l[i])-R; r[i]=std::lower_bound(R+1,R+m+1,r[i])-R; }
		fr(i,1,m+1) fr(j,1,m+1) f[i][j]=inf;
		fr(i,1,m+1) f[i][i-1]=0;
		fr(t,0,m-1) fr(i,1,m-t)
		{
			int j=i+t;
			static int H[N];
			fr(k,i,j) H[k]=0;
			fr(k,1,n) if(l[k]>=i&&r[k]<=j)
			{
				int p=l[k];
				for(;p+3<=r[k];p+=4)
				{
					if(H[p]<h[k]) H[p]=h[k];
					if(H[p+1]<h[k]) H[p+1]=h[k];
					if(H[p+2]<h[k]) H[p+2]=h[k];
					if(H[p+3]<h[k]) H[p+3]=h[k];
				}
				for(;p<=r[k];p++) if(H[p]<h[k]) H[p]=h[k];
			}
			fr(k,i,j) f[i][j]=std::min(f[i][j],f[i][k-1]+f[k+1][j]+H[k]);
		}
		printf("%d\n",f[1][m]);
	}
	return 0;
}
