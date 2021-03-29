/***************************************************************
	File name: L.cpp
	Author: huhao
	Create time: Tue 03 Nov 2020 03:01:54 PM CST
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
const int N=110;
int a[N][N],n,m;
int x[N][N],y[N][N],p[N][N];
int X,Y,P;
inline int Mod(int u,int n){ return (u%n+n)%n; }
inline int Div(int u,int n){ return u/n-(u%n&&u<0); }
#define mod Mod
#define div Div
int gcd(int u,int v){ return v?gcd(v,u%v):u; }
void modify(int u,int v)
{
//	printf("+ %d %d\n",u,v);
	int g=gcd(u,v); u/=g; v/=g;
	if(u<0){ u=-u; v=-v; }
	else if(u==0) v=std::abs(v);
	if(P==0){ P=1; X=u; Y=v; }
	else if(P==1){ if(u!=X||v!=Y) P=-1; }
}
void dfs(int u,int v)
{
//	printf("%d %d\n",u,v);
	int _x=div(u,n),x_=mod(u,n),_y=div(v,m),y_=mod(v,m);
	if(!a[x_][y_]) return ;
	if(p[x_][y_])
	{
		if(_x!=x[x_][y_]||_y!=y[x_][y_]) modify(_x-x[x_][y_],_y-y[x_][y_]);
		return ;
	}
	p[x_][y_]=1; x[x_][y_]=_x; y[x_][y_]=_y;
	dfs(u+1,v); dfs(u-1,v); dfs(u,v+1); dfs(u,v-1);
}
int main()
{
	n=read(); m=read();
	fr(i,0,n-1)
	{
		static char s[N]; scanf("%s",s);
		fr(j,0,m-1) a[i][j]=(s[j]=='.');
	}
	dfs(0,0);
/*	fr(i,0,n-1) fr(j,0,m-1) printf("%d%c",p[i][j],j==m-1?'\n':' ');
	putchar(10);
	fr(i,0,n-1) fr(j,0,m-1) printf("%d%c",x[i][j],j==m-1?'\n':' ');
	putchar(10);
	fr(i,0,n-1) fr(j,0,m-1) printf("%d%c",y[i][j],j==m-1?'\n':' ');
	printf("%d %d %d\n",P,X,Y);*/
	fr(T,1,read())
	{
		int u=read(),v=read();
		int _x=div(u,n),x_=mod(u,n),_y=div(v,m),y_=mod(v,m);
		int flag=1;
		if(!p[x_][y_]) flag=0;
		_x-=x[x_][y_]; _y-=y[x_][y_];
		if(P==1)
		{
			if(X==0){ if(_x||_y%Y) flag=0; }
			else if(Y==0){ if(_y||_x%X) flag=0; }
			else if(_x%X||_y%Y||_x/X!=_y/Y) flag=0;
		}
		else if(P==0){ if(_x||_y) flag=0; }
		printf("%s\n",flag?"yes":"no");
	}
	return 0;
}
