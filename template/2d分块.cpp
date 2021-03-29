/***************************************************************
	File name: 2d分块.cpp
	Author: huhao
	Create time: Fri 22 May 2020 07:32:24 PM CST
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
#define i64 long long
const int N=300010;
namespace solve // work in O(sqrt) modify and O(1) query
{
	// 0-index
	int n,m,wn,wm,vn,vm;
	i64 *a[N],*s1[N],*s2[N],*s3[N],*s4[N];
	void allocate(int _n,int _m)
	{
		n=_n; m=_m; wn=sqrt(n); wm=sqrt(m); vn=(n-1)/wn; vm=(m-1)/wm;
		fr(i,0,n+2){ s1[i]=new i64[m+2]; s2[i]=new i64[m+2]; s3[i]=new i64[m+2]; s4[i]=new i64[m+2]; a[i]=new i64[m+2]; }
		fr(i,0,n) fr(j,0,m) a[i][j]=s1[i][j]=s2[i][j]=s3[i][j]=s4[i][j]=0;
	}
	void init()
	{
		fr(i,0,n) fr(j,0,m) s1[i][j]=s2[i][j]=s3[i][j]=s4[i][j]=0;
		fr(i,0,n-1) fr(j,0,m-1)
		{
			s1[i/wn][j/wm]+=a[i][j];
			s2[i/wn][j]+=a[i][j];
			s3[i][j/wm]+=a[i][j];
			s4[i][j]+=a[i][j];
		}
		fr(i,0,vn) fr(j,1,vm) s1[i][j]+=s1[i][j-1];
		fr(i,1,vn) fr(j,0,vm) s1[i][j]+=s1[i-1][j];	
		fr(j,0,m-1) fr(i,1,vn) s2[i][j]+=s2[i-1][j];
		fr(j,0,m-1) if(j%wm) fr(i,0,vm) s2[i][j]+=s2[i][j-1];
		fr(i,0,n-1) fr(j,1,vm) s3[i][j]+=s3[i][j-1];
		fr(i,0,n-1) if(i%wn) fr(j,0,vm) s3[i][j]+=s3[i-1][j];

		fr(i,0,n-1) fr(j,0,m-1)
		{
			if(i%wn&&j%wm) s4[i][j]+=s4[i-1][j]+s4[i][j-1]-s4[i-1][j-1];
			else if(i%wn) s4[i][j]+=s4[i-1][j];
			else if(j%wm) s4[i][j]+=s4[i][j-1];
		}
	}
	void modify(int x,int y,i64 w) // Add (x,y) w
	{
		a[x][y]+=w;
		fr(i,x/wn,vn) fr(j,y/wm,vm) s1[i][j]+=w;
		fr(i,x/wn,vn) fr(j,y,(y/wm+1)*wm-1) s2[i][j]+=w;
		fr(i,x,(x/wn+1)*wn-1) fr(j,y/wm,vm) s3[i][j]+=w;
		fr(i,x,(x/wn+1)*wn-1) fr(j,y,(y/wm+1)*wm-1) s4[i][j]+=w;
	}
	i64 query(i64 x,i64 y)// query (a,b), a\in[0,x] b\in[0,y]
	{ return (x>=wn&&y>=wm?s1[x/wn-1][y/wm-1]:0)+(x>=wn?s2[x/wn-1][y]:0)+(y>=wm?s3[x][y/wm-1]:0)+s4[x][y]; }
}
namespace Solve // work in O(1) modify and O(sqrt) query
{
	int n,m,wn,wm,vn,vm;
	i64 *a[N],*s1[N],*s2[N],*s3[N],*s4[N];
	void allocate(int _n,int _m)
	{
		n=_n; m=_m; wn=sqrt(n); wm=sqrt(m); vn=(n-1)/wn; vm=(m-1)/wm;
		fr(i,0,n+2){ s1[i]=new i64[m+2]; s2[i]=new i64[m+2]; s3[i]=new i64[m+2]; s4[i]=new i64[m+2]; a[i]=new i64[m+2]; }
		fr(i,0,n) fr(j,0,m) a[i][j]=s1[i][j]=s2[i][j]=s3[i][j]=s4[i][j]=0;
	}
	void init()
	{
		fr(i,0,n) fr(j,0,m) s1[i][j]=s2[i][j]=s3[i][j]=s4[i][j]=0;
		fr(i,0,n-1) fr(j,0,m-1)
		{
			s1[i/wn][j/wm]+=a[i][j];
			s2[i/wn][j]+=a[i][j];
			s3[i][j/wm]+=a[i][j];
			s4[i][j]+=a[i][j];
		}
	}
	void modify(int x,int y,i64 w) // Add (x,y) w
	{
		a[x][y]+=w; s1[x/wn][y/wm]+=w; s2[x/wn][y]+=w; s3[x][y/wm]+=w; s4[x][y]+=w;
	}
	i64 query(i64 x,i64 y)// query (a,b), a\in[0,x] b\in[0,y]
	{
		i64 ans=0; int X=(x/wn)*wn,Y=(y/wm)*wm;
		fr(i,0,x/wn-1) fr(j,0,y/wm-1) ans+=s1[i][j];
		fr(i,0,x/wn-1) fr(j,Y,y) ans+=s2[i][j];
		fr(i,0,y/wm-1) fr(j,X,x) ans+=s3[j][i];
		fr(i,X,x) fr(j,Y,y) ans+=s4[i][j];
		return ans;
	}
}
int main()
{
	return 0;
}
