/***************************************************************
	File name: K.cpp
	Author: huhao
	Create time: Mon 26 Oct 2020 03:49:39 PM CST
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
const int N=110;
const int m=25;
const int p[N]={2,3,5,7,11, 13,17,19,23,29, 31,37,41,43,47, 53,59,61,67,71, 73,79,83,89,97};
double ans;
int vis3[81],           s3[81];
int vis2[27][64],       s2[27][64];
int vis7[27][16][49],   s7[27][16][49];
int vis5[27][16][7][25],s5[27][16][7][25];
std::bitset<N> vis[27][16][7][5][25];
int s[27][16][7][5][25];
double Ans[27][16][7][5];
int flag=0;
void Add(int a,int b)
{
	if(a==1){ flag=1; return ; }
	if(a==81)
	{
		if(!vis3[b]){ vis3[b]=1; s3[b%27]++; }
		return ;
	}
	int mx=0;
	fr(i,0,m-1) if(a%p[i]==0) mx=i;
//	printf("+ %d %d  %d\n",a,b,mx);
	fr(i3,0,26)
	{
		int _a=a,_b=b;
#define If(x,y,s) if(a%x==0){ if(b%x==y%x){ if(a==x){ s[y]=100; continue; } } else continue; a/=x; b%=a; }
		If(27,i3,s3)
		else If(9,i3,s3)
		else If(3,i3,s3);

		if(a==64)
		{
			if(!vis2[i3][b]){ vis2[i3][b]=1; s2[i3][b%16]++; }
		}
		else
		if(a==32)
		{
			if(!vis2[i3][b]){ vis2[i3][b]=1; s2[i3][b%16]++; }
			if(!vis2[i3][b+32]){ vis2[i3][b+32]=1; s2[i3][b%16]++; }
		}
		else
		fr(i2,0,15)
		{
			int _a=a,_b=b;
			If(16,i2,s2[i3])
			else If(8,i2,s2[i3])
			else If(4,i2,s2[i3])
			else If(2,i2,s2[i3]);

			if(a==49)
			{
				if(!vis7[i3][i2][b]){ vis7[i3][i2][b]=1; s7[i3][i2][b%7]++; }
			}
			else
			fr(i7,0,6)
			{
				int _a=a,_b=b;
				If(7,i7,s7[i3][i2]);

				if(a==25)
				{
					if(!vis5[i3][i2][i7][b]){ vis5[i3][i2][i7][b]=1; s5[i3][i2][i7][b%5]++; }
				}
				else
				fr(i5,0,4)
				{
					int _a=a,_b=b;
					If(5,i5,s5[i3][i2][i7]);

					if(vis[i3][i2][i7][i5][mx][b]) ;
					else
					{
						vis[i3][i2][i7][i5][mx][b]=1; int k=s[i3][i2][i7][i5][mx]++;
						Ans[i3][i2][i7][i5]*=1.*(p[mx]-k-1)/(p[mx]-k);
					}
					a=_a; b=_b;
				}
				a=_a; b=_b;
			}
			a=_a; b=_b;
		}
		a=_a; b=_b;
	}
}
int main()
{
	static int vis[N][N];
	fr(i,0,26) fr(j,0,15) fr(k,0,6) fr(l,0,4) Ans[i][j][k][l]=1;
	ans=1;
	fr(T,1,read())
	{
		int s=read(),x=read(),y=read(); double lans=ans;
		fr(i,0,x-1)
		{
			int a=x+y,b=((i-s)%(x+y)+(x+y))%(x+y);
			if(vis[a][b]) continue;
			else{ vis[a][b]=1; Add(a,b); }
		}
		ans=0;
		using std::max;
//		fr(i,0,26) fr(j,0,15) printf("%d%c",s2[i][j],j==15?'\n':' ');
		if(!flag) fr(i,0,26) fr(j,0,15) fr(k,0,6) fr(l,0,4)
		{
			ans+=Ans[i][j][k][l]*max(0,3-s3[i])/3.*max(0,4-s2[i][j])/4.*max(0,7-s7[i][j][k])/7.*max(0,5-s5[i][j][k][l])/5./27./16./7./5.;
//			printf("%.10lf  %d %d %d %d\n",Ans[i][j][k][l],s3[i],s2[i][j],s7[i][j][k],s5[i][j][k][l]);
		}
		printf("%.10lf\n",lans-ans);
	}
	printf("%.10lf\n",ans);
	return 0;
}
