/***************************************************************
	File name: G.cpp
	Author: huhao
	Create time: Wed 21 Oct 2020 08:23:43 PM CST
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
const int N=310;
int n,m,a[N][N],b[N][N],c[N][N];
void simplify()
{
	int x=n+1,y=m+1,X=0,Y=0;
	fr(i,1,n) fr(j,1,m) if(b[i][j])
	{
		x=std::min(x,i); X=std::max(X,i);
		y=std::min(y,j); Y=std::max(Y,j);
	}
	if(x==n+1){ n=m=0; return ; }
	n=X-x+1; m=Y-y+1;
	fr(i,x,X) fr(j,y,Y) a[i-x+1][j-y+1]=b[i][j];
}
inline int dif(int x,int y){ return a[x][y]^c[x][y]; }
int solve()
{
	fr(i,0,n+1) fr(j,0,m+1) if(i==0||i==n+1||j==0||j==m+1) a[i][j]=0;
	fr(i,0,n+1) fr(j,0,m+1) b[i][j]=c[i][j]=0;
	fr(i,1,n)
	{
		fr(j,1,m) if(dif(i-1,j-1))
		{
			b[i][j]^=1;
			fr(x,-1,1) fr(y,-1,1) c[i+x][j+y]^=1;
		}
	}
/*	fr(i,0,n+1)
	{
		fr(j,0,m+1) putchar(dif(i,j)?'#':'.');
		putchar(10);
	}*/
	int I=0,J=0;
	while(I<=n+1&&!dif(I,m)&&!dif(I,m+1)) I++;
	while(J<=m+1&&!dif(n,J)&&!dif(n+1,J)) J++;
	if(I==n+2&&J==m+2){ simplify(); return 1; }
	else if(I==n+2) I=dif(n,J)?n:n+1;
	else if(J==m+2) J=dif(I,m)?m:m+1;
	c[I][J]^=1; //printf("%d %d\n",I,J);
	fr(i,1,n)
	{
		fr(j,1,m) if(dif(i-1,j-1))
		{
			b[i][j]^=1;
			fr(x,-1,1) fr(y,-1,1) c[i+x][j+y]^=1;
		}
	}
	fr(i,0,n+1) fr(j,0,m+1) if(dif(i,j)) return 0;
	simplify(); return 1;
}
int main()
{
	m=read(); n=read();
	fr(i,1,n)
	{
		static char s[N];
		scanf("%s",s+1);
		fr(j,1,m) b[i][j]=(s[j]=='#');
	}
	simplify();
	while(n&&m&&solve()) ;
	if(n)
	{
		fr(i,1,n)
		{
			fr(j,1,m) putchar(a[i][j]?'#':'.');
			putchar(10);
		}
	}
	else printf("#\n");
	return 0;
}
