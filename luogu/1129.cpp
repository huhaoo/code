/****************************************************************
	File name: 1129.cpp
	Author: huhao
	Email: 826538400@qq.com
	Create time: 8/14/2018, 7:20:02 PM
****************************************************************/
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
#define N 210
int T,n,a[N][N],p[N],vis[N];
int check(int u)
{
	if(vis[u])return 0;vis[u]=1;
	fr(v,1,n)if(a[u][v]&&!p[v]){p[v]=u;return 1;}
	fr(v,1,n)if(a[u][v]&&check(p[v])){p[v]=u;return 1;}
	return 0;
}
int main()
{
	T=read();
	while(T--)
	{
		n=read();
		fr(i,1,n)fr(j,1,n)a[i][j]=read();
		fr(i,1,n)p[i]=0;
		fr(i,1,n)
		{
			fr(j,1,n)vis[j]=0;
			if(!check(i)){printf("No\n");goto end;}
		}
		printf("Yes\n");
		end:;
	}
	return 0;
}