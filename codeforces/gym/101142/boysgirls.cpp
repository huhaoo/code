/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Wed 21 Oct 2020 04:08:07 PM CST
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
const int N=100010;
int n,x,y,a[N];
int check(int n,int x,int y)
{
	int d=x+y-n;
	return x>=d&&y>=d&&d>=0&&d<=n&&d%2==0&&((d==0)==(x==0||y==0));
}
void solve(int *p,int *a,int n,int x,int y)
{
	int d=x+y-n,m=0;
	fr(i,0,d/2-1){ a[p[m++]]=1; a[p[m++]]=0; }
	fr(i,0,y-d-1) a[p[m++]]=0;
	fr(i,0,x-d-1) a[p[m++]]=1;
/*	printf("%d %d %d\n",n,x,y);
	fr(i,0,n-1) putchar(a[p[i]]+48);
	putchar(10);*/
}
int main()
{
	freopen("boysgirls.in","r",stdin); freopen("boysgirls.out","w",stdout);
	n=read(); x=read(); y=read();
	int flag=1;
	if(n&1)
	{
		static int p[N];
		fr(i,0,n-1) p[i]=i*2%n;
		if(check(n,x,y)) solve(p,a,n,x,y);
		else flag=0;
	}
	else
	{
		int x1=0,y1=0;
		flag=0;
		if(check(n/2,x-n/2,y)){ flag=1; x1=n/2; }
		else if(check(n/2,x,y-n/2)){ flag=1; y1=n/2; }
		else
		{
			x1=std::min(n/2,x); y1=std::min(n/2,y);
			if((x1+y1-n/2)%2==1) (x-x1<y-y1?x1:y1)--;
//			printf("%d %d %d %d\n",x1,y1,x-x1,y-y1);
			if(check(n/2,x1,y1)&&check(n/2,x-x1,y-y1)) flag=1;
		}
		if(flag)
		{
			static int p[N];
			fr(i,0,n/2-1) p[i]=i*2;
			solve(p,a,n/2,x1,y1);
			fr(i,0,n/2-1) p[i]=i*2+1;
			solve(p,a,n/2,x-x1,y-y1);
		}
	}
	if(!flag){ printf("Impossible\n"); return 0; }
	fr(i,0,n-1) putchar(a[i]?'B':'G');
	putchar(10);
	return 0;
}
