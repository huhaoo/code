/***************************************************************
	File name: digital.cpp
	Author: huhao
	Create time: Mon 04 Jan 2021 03:50:23 PM CST
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
const int C[10][5][2]=
{
	{
		{0,1},
		{1,1},
		{0,0},
		{1,1},
		{0,1}
	},
	{
		{0,0},
		{0,1},
		{0,0},
		{0,1},
		{0,0}
	},
	{
		{0,1},
		{0,1},
		{0,1},
		{1,0},
		{0,1}
	},
	{
		{0,1},
		{0,1},
		{0,1},
		{0,1},
		{0,1}
	},
	{
		{0,0},
		{1,1},
		{0,1},
		{0,1},
		{0,0}
	},
	{
		{0,1},
		{1,0},
		{0,1},
		{0,1},
		{0,1}
	},
	{
		{0,1},
		{1,0},
		{0,1},
		{1,1},
		{0,1}
	},
	{
		{0,1},
		{0,1},
		{0,0},
		{0,1},
		{0,0}
	},
	{
		{0,1},
		{1,1},
		{0,1},
		{1,1},
		{0,1}
	},
	{
		{0,1},
		{1,1},
		{0,1},
		{0,1},
		{0,1}
	},
};
#include<vector>
const int N=210;
int n,a[N][N],b[N];
int p[N][10][10][2];
void draw(int st,int i,int v){ fr(j,0,4) if(C[v][j][i]) b[j+st]=1; }
int main()
{
	freopen("digital.in","r",stdin); freopen("digital.out","w",stdout);
	n=read()+1;
	fr(i,1,9) fr(j,1+(i&1),n) a[i][j]=read();
	fr(i,0,n+1) fr(j,0,9) fr(k,0,9) fr(l,0,1) p[i][j][k][l]=-1;
	fr(i,0,9) fr(j,0,9)
	{
		int k=(i+j)%10;
		fr(o,1,9) b[o]=0;
		draw(1,1,i); draw(3,1,j); draw(5,1,k);
		int flag=1;
		fr(o,1,9) if(a[o][n]!=b[o]) flag=0;
		if(flag) p[n][i][j][0]=0;
	}
	fd(i,n-1,2) fr(j,0,9) fr(k,0,9) fr(u,0,9) fr(v,0,9) fr(d,0,1) if(p[i+1][u][v][d]!=-1)
	{
		int D=(u+v+d)/10,w=(u+v+d)%10,l=(j+k+D)%10;
		fr(o,1,9) b[o]=0;
		draw(1,1,j); draw(3,1,k); draw(5,1,l);
		draw(1,0,u); draw(3,0,v); draw(5,0,w);
		int flag=1;
		fr(o,1,9) if(a[o][i]!=b[o]) flag=0;
		if(flag) p[i][j][k][D]=d*100+u*10+v;
	}
	fr(i,0,9) fr(j,0,9) fr(d,0,1) if(p[2][i][j][d]!=-1)
	{
		int k=i+j+d; if(k>9) continue;
		fr(o,1,9) b[o]=0;
		draw(1,0,i); draw(3,0,j); draw(5,0,k);
		int flag=1;
		fr(o,1,9) if(a[o][1]!=b[o]) flag=0;
		if(flag)
		{
			std::vector<int> A,B,C;
			fr(o,2,n)
			{
				A.push_back(i); B.push_back(j); C.push_back(k);
				int lst=p[o][i][j][d];
				d=lst/100; i=lst%100/10; j=lst%10; k=(i+j+d)%10;
			}
			for(auto o:A) printf("%d",o);; putchar(10);
			for(auto o:B) printf("%d",o);; putchar(10);
			for(auto o:C) printf("%d",o);; putchar(10);
			return 0;
		}
	}
	printf("NO\n");
	return 0;
}
