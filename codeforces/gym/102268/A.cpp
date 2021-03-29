/***************************************************************
	File name: A.cpp
	Author: huhao
	Create time: Thu 06 Aug 2020 07:59:19 PM CST
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
#include<vector>
const int N=110,M=20010;
int n,m,c,id[N][N],x[M],y[M];
int a[N][N];
char s[N][N];
std::vector<int> e[M];
int p[M];
void Add(int u,int v)
{
	if(!u||!v) return ;
//	printf("%d %d\n",u,v);
	e[u].push_back(v); e[v].push_back(u);
	if(!p[u]&&!p[v]){ p[u]=v; p[v]=u; }
}
int f[M],vis[M],q[M],l,r,Vis[M],T,pre[M];
int getf(int u){ return u==f[u]?f[u]:f[u]=getf(f[u]); }
void flower(int u,int v,int l)
{
	while(getf(u)!=l)
	{
		pre[u]=v; v=p[u];
		if(f[u]==u) f[u]=l;
		if(f[v]==v) f[v]=l;
		if(vis[v]==1){ vis[v]=0; q[++r]=v; }
		u=pre[v];
	}
}
int lca(int u,int v)
{
	T++;
	while(1)
	{
		u=getf(u);
		if(Vis[u]==T) return u;
		Vis[u]=T; u=pre[p[u]];
		if(v) std::swap(u,v);
	}
}
void solve(int st)
{
	fr(i,1,c){ vis[i]=-1; f[i]=i; pre[i]=0; }
	q[l=r=1]=st; vis[st]=0;
	while(l<=r)
	{
		int u=q[l++];
		for(auto v:e[u])
			if(vis[v]==-1)
			{
				if(!p[v])
				{
					int lst=0;
//					printf("%d  %d %d\n",st,u,v);
					while(u&&v){ lst=p[u]; p[u]=v; p[v]=u; v=lst; u=pre[v]; }
					return ;
				}
				vis[v]=1; pre[v]=u; vis[p[v]]=0; q[++r]=p[v];
			}
			else if(!vis[v]&&getf(u)!=getf(v)){ int l=lca(u,v); flower(u,v,l); flower(v,u,l); }
	}
}
int ans[N][N],Ans;
char out[N][N];
int color(int x,int y,int c)
{
	out[x][y]=c; int rt=1; static int X[]={1,-1,0,0},Y[]={0,0,1,-1};
	fr(i,0,3)
		if(ans[x][y]==ans[x+X[i]][y+Y[i]])
		{
			if(out[x+X[i]][y+Y[i]]!=c) rt&=color(x+X[i],y+Y[i],c);
		}
		else if(out[x+X[i]][y+Y[i]]==c) rt=0;
	return rt;
}
int main()
{
	n=read(); m=read();
	fr(i,0,n+1) fr(j,0,m+1) a[i][j]=-1;
	fr(i,1,n)
	{
		static char s[N]; scanf("%s",s+1);
		fr(j,1,m) a[i][j]=(s[j]=='.'?0:s[j]=='+'?1:2);
	}
	fr(i,1,n) fr(j,1,m)
	{
		if(a[i][j])
		{
			id[i][j]=++c; c++; Add(c-1,c);
		}
		else id[i][j]=++c;
		x[c]=i; y[c]=j;
	}
	fr(i,1,n) fr(j,1,m) if(a[i][j])
	{
		if(!a[i-1][j]){ Add(id[i][j],id[i-1][j]); if(a[i][j]==1) Add(id[i][j]+1,id[i-1][j]); }
		if(!a[i+1][j]){ Add(id[i][j],id[i+1][j]); if(a[i][j]==1) Add(id[i][j]+1,id[i+1][j]); }
		if(!a[i][j-1]){ Add(id[i][j]+1,id[i][j-1]); if(a[i][j]==1) Add(id[i][j],id[i][j-1]); }
		if(!a[i][j+1]){ Add(id[i][j]+1,id[i][j+1]); if(a[i][j]==1) Add(id[i][j],id[i][j+1]); }
	}
//	fr(i,1,c) printf("%d%c",p[i],i==c?'\n':' ');
	fr(i,1,c) if(!p[i]) solve(i);
//	fr(i,1,c) printf("%d%c",p[i],i==c?'\n':' ');
	fr(i,1,n) fr(j,1,m) if(a[i][j]&&p[id[i][j]]!=id[i][j]+1)
	{
		Ans++; ans[i][j]=ans[x[p[id[i][j]]]][y[p[id[i][j]]]]=ans[x[p[id[i][j]+1]]][y[p[id[i][j]+1]]]=Ans;
	}
	fr(i,1,n) fr(j,1,m) if(!ans[i][j]) out[i][j]=(a[i][j]==0?'.':a[i][j]==1?'+':'*');
	fr(i,1,n) fr(j,1,m) if(!out[i][j])
	{
		fr(c,'a','z') if(color(i,j,c)) break;
	}
	fr(i,1,n) printf("%s\n",out[i]+1);
	return 0;
}
