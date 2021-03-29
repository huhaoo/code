/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Thu 05 Nov 2020 04:57:09 PM CST
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
#include<vector>
const int N=510;
int T,vis[N][N];
int d[N][N][15];
double dis(double a,double b,double c,double d)
{
	return sqrt((a-c)*(a-c)+(b-d)*(b-d));
}
double dis(double a,double b,double c,double d,double e,double f)
{
	if(e+1e-9<a||e-1e-9>c||f+1e-9<std::min(b,d)||f-1e-9>std::max(b,d)) return 1234567890;
	return fabs((a-e)*(d-f)-(c-e)*(b-f))/dis(a,b,c,d);
}
int solve(int x,int y,double a,double b,double c,double d)
{
	if(vis[x][y]==T) return 0;
	vis[x][y]=T; double r=dis(a,b,c,d,x,y);
	if(r>1) return 0;
	return ::d[x][y][int(r*10+0.999999)];
}
int main()
{
	fr(i,1,read())
	{
		int x=read(),y=read(); double r; scanf("%lf",&r);
		fr(j,0,int(r*10+0.5)) d[x][y][j]++; 
	}
	fr(i,1,read())
	{
		int a=read(),b=read(),c=read(),d=read();
		if(a>c){ std::swap(a,c); std::swap(b,d); }
		int x=a,y=b; T++;
		int ans=0;
		while(1)
		{
//			printf("%d %d  %.10lf\n",x,y,dis(a,b,c,d,x,y));
			fr(X,-1,1) fr(Y,-1,1) if(X==0||Y==0) ans+=solve(x+X,y+Y,a,b,c,d);
			if(x==c&&y==d) break;
			int _x=x,_y=y; if(b<d) _y++; else _y--;
			if(dis(a,b,c,d,x+1,y)<dis(a,b,c,d,_x,_y)) x++;
			else y=_y;
			if(x==0||x==501||y==0||y==501) return 0;
		}
		printf("%d\n",ans);
	}
	return 0;
}
