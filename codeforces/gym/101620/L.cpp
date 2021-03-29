/***************************************************************
	File name: L.cpp
	Author: huhao
	Create time: Tue 24 Nov 2020 03:38:12 PM CST
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
const int N=4020,D=2005;
int n,s1[N][N],s2[N][N],s[4][N][N];
int ans;
int main()
{
	n=D*2;
	fr(T,1,read())
	{
		char c=0; while(c!='A'&&c!='B') c=getchar();
		int x=read()+D,y=read()+D,l=read()/2;
		if(c=='A')
		{
			s1[x-l][y-l]++; s1[x+l][y-l]--; s1[x-l][y+l]--; s1[x+l][y+l]++;
		}
		else
		{
			s2[x][y-l]++; s2[x-l][y]--; s2[x+l][y]--; s2[x][y+l]++;
		}
	}
	fr(j,1,n) fr(i,1,n)
	{
		if(s1[i][j])
		{
//			printf("A %d %d\n",i-D,j-D);
			s[0][i][j]=s[1][i][j]=s[2][i][j]=s[3][i][j]=1;
		}
		if(s2[i][j])
		{
//			printf("B %d %d\n",i-D,j-D);
			s[0][i][j]=s[3][i][j]=1;
			s[0][i-1][j]=s[1][i-1][j]=1;
			s[2][i][j+1]=s[3][i][j+1]=1;
			s[1][i-1][j+1]=s[2][i-1][j+1]=1;
		}
		s1[i+1][j]+=s1[i][j]; s1[i][j+1]+=s1[i][j]; s1[i+1][j+1]-=s1[i][j];
		s2[i+1][j+1]+=s2[i][j]; s2[i-1][j+1]+=s2[i][j]; s2[i][j+2]-=s2[i][j];
	}
	fr(i,1,n) fr(j,1,n) fr(k,0,3) ans+=s[k][i][j];
	printf("%.2f\n",ans*0.25);
	return 0;
}
