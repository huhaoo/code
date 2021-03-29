/***************************************************************
	File name: A.cpp
	Author: huhao
	Create time: Wed 25 Nov 2020 09:46:02 AM CST
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
const int N=1034;
int n,f[N],s,_f[N][N];
int a[N][N];
std::vector<int> e[N];
void Max(int &a,int b){ if(a<b) a=b; }
int Solve(int u,int w,int F,int p)
{
	int ans=s+a[u][w]+f[u];
	for(auto v:e[u]) if(v!=F){ s+=_f[u][v]; Max(ans,Solve(v,w,u,p)); s-=_f[u][v]; }
	return ans;
}
int solve(int u,int w,int F,int p)
{
	s+=f[u]; int ans=Solve(w,u,p,p); s-=f[u];
	for(auto v:e[u]) if(v!=F){ s+=_f[u][v]; Max(ans,solve(v,w,u,p)); s-=_f[u][v]; }
	return ans;
}
void dfs(int u,int F)
{
	for(auto v:e[u]) if(v!=F) dfs(v,u);
	s=0;
	static int m,a[N],G[N],g[N][N],h[N]; m=0;
	for(auto v:e[u]) if(v!=F){ s=0; G[a[v]=m++]=Solve(v,u,u,u); }
	fr(i,0,m-1) fr(j,0,m-1) g[i][j]=0;
	for(auto v:e[u]) for(auto w:e[u]) if(v!=F&&w!=F&&v!=w){ s=0; g[a[v]][a[w]]=g[a[w]][a[v]]=solve(v,w,u,u); }
	fr(i,0,(1<<m)-1) h[i]=0;
	fr(i,0,(1<<m)-2)
	{
		int u=0;
		while((i>>u)&1) u++;
		Max(h[i|(1<<u)],h[i]+G[u]);
		fr(v,u+1,m-1) if(!((i>>v)&1)) Max(h[i|(1<<u)|(1<<v)],h[i]+g[u][v]);
		u++;
		while(u<m&&((i>>u)&1)) u++;
		if(u==m) continue; 
		Max(h[i|(1<<u)],h[i]+G[u]);
		fr(v,u+1,m-1) if(!((i>>v)&1)) Max(h[i|(1<<u)|(1<<v)],h[i]+g[u][v]);
	}
	f[u]=h[(1<<m)-1];
	for(auto i:e[u]) _f[u][i]=h[(1<<m)-1-(1<<a[i])];
}
int main()
{
	fr(T,1,read())
	{
		n=read();
		fr(i,1,n) fr(j,1,n) a[i][j]=0;
		fr(i,1,n){ e[i].clear(); f[i]=0; }
		fr(i,1,n-1){ int u=read(),v=read(); e[u].push_back(v); e[v].push_back(u); }
		fr(m,1,read()){ int u=read(),v=read(); a[u][v]=a[v][u]=1; }
		dfs(1,0);
		printf("%d\n",f[1]);
	}
	return 0;
}
