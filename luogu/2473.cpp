/**************************************************************
	File name: 2473.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/20/2018, 2:46:37 PM
**************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
using namespace std;
#define fr(i,a,b) for(int i=(a),_end_=(b);i<=_end_;i++)
#define fd(i,a,b) for(int i=(a),_end_=(b);i>=_end_;i--)
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
#define M 110
#define N 20
int m,n,p[N],w[N],vis[M][1<<N];
double f[M][1<<N];
double dfs(int x,int y)
{
	if(x==m)return 0;
	if(vis[x][y])return f[x][y];
	vis[x][y]=1;
	fr(i,1,n)if((y&p[i])==p[i])f[x][y]+=max(w[i]+dfs(x+1,y|(1<<(i-1))),dfs(x+1,y));
	else f[x][y]+=dfs(x+1,y);
	f[x][y]/=n;
	return f[x][y];
}
int main()
{
	m=read();n=read();
	fr(i,1,n)
	{
		w[i]=read();int a=read();
		while(a)p[i]|=1<<(a-1),a=read();
	}
	printf("%.6lf\n",dfs(0,0));
	return 0;
}