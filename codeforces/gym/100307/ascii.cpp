/***************************************************************
	File name: ascii.cpp
	Author: huhao
	Create time: Sun 01 Nov 2020 02:17:34 PM CST
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
const int N=40;
int k,w,h,n;
int a[N][N][N];
int A[N][N];
int op[N],Op[N][N],p[N],id[N][N];
void dfs(int x,int y)
{
	if(x==n+1)
	{
//		fr(i,1,n) fr(j,1,n) printf("%d%c",id[i][j],j==n?'\n':' ');
//		putchar(10);
		memset(A,0,sizeof(A));
		fr(i,1,n) fr(j,1,n) fr(I,1,h*3) fr(J,1,w*3)
			if(a[id[i][j]][I][J]) A[(i-1)*h+I-h][(j-1)*w+J-w]++;
		int flag=1;
		fr(i,1,h*n) fr(j,1,w*n) if(A[i][j]!=1) flag=0;
		if(flag)
		{
			printf("%d %d\n",w*n,h*n);
			fr(i,1,n) fr(j,1,n) fr(I,1,h*3) fr(J,1,w*3)
				if(a[id[i][j]][I][J]) A[(i-1)*h+I-h][(j-1)*w+J-w]=id[i][j];
			fr(i,1,h*n)
			{
				fr(j,1,w*n) putchar(A[i][j]+'A'-1);
				putchar(10);
			}
			exit(0);
		}
		return ;
	}
	if(y==n+1){ dfs(x+1,1); return ; }
	fr(i,1,k) if(Op[x][y]==op[i]&&!p[i]){ p[i]=1; id[x][y]=i; dfs(x,y+1); p[i]=0; }
}
int main()
{
	freopen("ascii.in","r",stdin); freopen("ascii.out","w",stdout);
	k=read(); w=read(); h=read();
	switch(k)
	{
		case 16: n++;
		case 9: n++;
		case 4: n++;
		case 1: n++;
	}
	if(n==1){ printf("%d %d\n",w,h); fr(i,1,h){ fr(i,1,w) putchar('A'); putchar(10); } }
	Op[1][1]=1; Op[1][n]=3; Op[n][1]=7; Op[n][n]=9;
	fr(i,2,n-1) Op[1][i]=2;
	fr(i,2,n-1) Op[i][1]=4;
	fr(i,2,n-1) Op[i][n]=6;
	fr(i,2,n-1) Op[n][i]=8;
	fr(i,2,n-1) fr(j,2,n-1) Op[i][j]=5;
//	fr(i,1,n) fr(j,1,n) printf("%d%c",Op[i][j],j==n?'\n':' ');
	fr(t,1,k)
	{
		static char s[N];
		fr(i,2,h*3-1)
		{
			scanf("%s",s+2);
			fr(j,2,w*3-1) a[t][i][j]=(s[j]!='.');
		}
		int p1=1,p2=1,p3=1,p4=1;
		fr(i,1,h+1) fr(j,w+1,w+w) if(a[t][i][j]!=(i==h+1)) p1=0;
		fr(i,h+1,h+h) fr(j,1,w+1) if(a[t][i][j]!=(j==w+1)) p2=0;
		fr(i,h+1,h+h) fr(j,w*2,w*3) if(a[t][i][j]!=(j==w*2)) p3=0;
		fr(i,h*2,h*3) fr(j,w+1,w+w) if(a[t][i][j]!=(i==h*2)) p4=0;
		// 1   123
		//2o3  456
		// 4   789
		if(p1&&p2) op[t]=1;
		else if(p1&&p3) op[t]=3;
		else if(p2&&p4) op[t]=7;
		else if(p3&&p4) op[t]=9;
		else if(p1) op[t]=2;
		else if(p2) op[t]=4;
		else if(p3) op[t]=6;
		else if(p4) op[t]=8;
		else op[t]=5;
//		fr(i,1,h*3) fr(j,1,w*3) printf("%d%c",a[t][i][j],j==w*3?'\n':' ');
//		printf("%d %d %d %d\n",p1,p2,p3,p4);
	}
//	fr(i,1,k) printf("%d%c",op[i],i==k?'\n':' ');
	dfs(1,1);
	return 0;
}
