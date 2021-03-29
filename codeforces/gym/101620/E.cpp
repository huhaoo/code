/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Thu 19 Nov 2020 11:00:18 AM CST
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
const int N=300010,mod=1000000007;
int n,d[N],D[N],s[N],f[N],c[N];
std::vector<int> e[N];
void _dfs(int u,int f=0)
{
	d[u]=d[f]+1; D[u]=1;
	fr(i,0,e[u].size()-1) if(e[u][i]==f){ e[u].erase(e[u].begin()+i); break; }
	for(auto v:e[u]){ _dfs(v,u); D[u]=std::max(D[u],D[v]+1); }
	c[u]=e[u].size();
	if(c[u]>2){ printf("0\n"); exit(0); }
	else if(c[u]>1) s[u]=u;
	else if(c[u]) s[u]=s[e[u][0]];
}
int solve(int u,int v)
{
	while(u&&v)
	{
		if(c[u]>1||c[v]>1) return 0;
		if(c[u]) u=e[u][0];
		else u=0;
		if(c[v]) v=e[v][0];
		else v=0;
	}
	if(!u&&!v) return 1;
	else if(!u) return f[v];
	else return f[u];
}
#define i64 long long
void dfs(int u)
{
	if(!c[u]){ f[u]=1; return ; }
	for(auto v:e[u]) dfs(v);
	i64 ans=0;
	if(c[u]==1)
	{
		if(!c[e[u][0]]){ f[u]=2; return ; }
		ans+=f[e[u][0]];
		if(c[e[u][0]]==1) ans+=f[e[e[u][0]][0]];
		int v=s[u];
		if(!v)
		{
			if(D[u]%2==0) ans++;
		}
		else
		{
			int l=d[v]-d[u];
			int w=e[v][0],x=e[v][1];
//			printf("%d %d  %d    %d %d  %d %d\n",u,v,l,w,x,D[w],D[x]);
			if(!s[w]&&(D[w]+1==l||D[w]-1==l)) ans+=f[x];
			if(!s[x]&&(D[x]+1==l||D[x]-1==l)) ans+=f[w];
			if(c[w]==2)
			{
				int y=e[w][0],z=e[w][1];
				if(!s[y]&&D[y]==l) ans+=solve(z,x);
				if(!s[z]&&D[z]==l) ans+=solve(y,x);
			}
			if(c[x]==2)
			{
				int y=e[x][0],z=e[x][1];
				if(!s[y]&&D[y]==l) ans+=solve(z,w);
				if(!s[z]&&D[z]==l) ans+=solve(y,w);
			}
		}
	}
	else
	{
		int v=e[u][0],w=e[u][1];
		if(c[v]==0) ans+=f[w];
		else if(c[v]==1) ans+=solve(e[v][0],w);
		if(c[w]==0) ans+=f[v];
		else if(c[w]==1) ans+=solve(e[w][0],v);
	}
	f[u]=ans%mod;
}
int main()
{
	n=read();
	fr(i,1,n-1){ int u=read(),v=read(); e[u].push_back(v); e[v].push_back(u); }
	_dfs(1); dfs(1);
//	fr(i,1,n) printf("%d%c",f[i],i==n?'\n':' ');
//	fr(i,1,n) printf("%d%c",s[i],i==n?'\n':' ');
	printf("%d\n",f[1]);
	return 0;
}
