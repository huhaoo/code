/***************************************************************
	File name: kids.cpp
	Author: huhao
	Create time: Sun 24 Jan 2021 02:56:37 PM CST
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
const int N=4010;
char s[N];
int n,m;
int a[N][N],b[N][N],c[N][N],d[N][N];
int xa,ya,xb,yb,xc,yc,x,y,flag;
void Xor(int d[N][N],int a[N][N],int dx,int dy){ fr(i,1,n) fr(j,1,n) if(a[i][j]) d[i+dx][j+dy]^=1; }
int main()
{
	freopen("kids.in","r",stdin); freopen("kids.out","w",stdout);
	n=read(); m=read();
	fr(i,1,n)
	{
		scanf("%s",s+1);
		fr(j,1,m) if((a[i][j]=s[j]=='*')&&!xa){ xa=i; ya=j; };
	}
	n=read(); m=read();
	fr(i,1,n)
	{
		scanf("%s",s+1);
		fr(j,1,m) if((b[i][j]=s[j]=='*')&&!xb){ xb=i; yb=j; };
	}
	n=read(); m=read();
	fr(i,1,n)
	{
		scanf("%s",s+1);
		fr(j,1,m) if((c[i][j]=s[j]=='*')&&!xc){ xc=i; yc=j; };
	}
	n=1000;

	memset(d,0,sizeof(d)); Xor(d,a,n-xa,n-ya); Xor(d,b,n-xb,n-yb); x=y=0; flag=1;
	fr(i,1,n+n) fr(j,1,n+n) if(d[i][j]&&!x){ x=i; y=j; }
	fr(i,0,n+n) fr(j,-n+n,n+n) if((j+y>0?d[i+x][j+y]:0)!=(j+yc>0?c[i+xc][j+yc]:0)) flag=0;
	if(flag){ printf("YES\n%d %d\n",ya-yb,xa-xb); return 0; }
//	fr(i,0,n+n){ fr(j,0,n+n) putchar(c[i][j]?'*':'.'); putchar(10); } putchar(10);
//	fr(i,0,n+n){ fr(j,0,n+n) putchar(d[i][j]?'*':'.'); putchar(10); } putchar(10);

	memset(d,0,sizeof(d)); Xor(d,a,n-xa,n-ya); Xor(d,c,n-xc,n-yc); x=y=0; flag=1;
	fr(i,1,n+n) fr(j,1,n+n) if(d[i][j]&&!x){ x=i; y=j; }
	fr(i,0,n+n) fr(j,-n+n,n+n) if((j+y>0?d[i+x][j+y]:0)!=(j+yb>0?b[i+xb][j+yb]:0)) flag=0;
	if(flag){ printf("YES\n%d %d\n",y-yb-n+ya,x-xb-n+xa); return 0; }
//	fr(i,0,n+n){ fr(j,0,n+n) putchar(b[i][j]?'*':'.'); putchar(10); } putchar(10);
//	fr(i,0,n+n){ fr(j,0,n+n) putchar(d[i][j]?'*':'.'); putchar(10); } putchar(10);

	memset(d,0,sizeof(d)); Xor(d,b,n-xb,n-yb); Xor(d,c,n-xc,n-yc); x=y=0; flag=1;
	fr(i,1,n+n) fr(j,1,n+n) if(d[i][j]&&!x){ x=i; y=j; }
	fr(i,0,n+n) fr(j,-n+n,n+n) if((j+y>0?d[i+x][j+y]:0)!=(j+ya>0?a[i+xa][j+ya]:0)) flag=0;
	if(flag){ printf("YES\n%d %d\n",-(y-ya-n)-yb,-(x-xa-n)-xb); return 0; }

	printf("NO\n");
	return 0;
}
