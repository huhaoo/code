/***************************************************************
	File name: hidden.cpp
	Author: huhao
	Create time: Mon 23 Nov 2020 10:26:33 AM CST
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
#define i64 long long
#define pii std::pair<int,int>
#define piii std::pair<int,pii>
#include<map>
#include<vector>
const int N=60010;
int n;
i64 ans,Ans;
std::map<int,int> e[N];
std::vector<int> E[N];
int t[2][N],c[N],d[N],D;
int w[N],f[N],W; pii r;
void dfs(int u)
{
	w[u]=1;
	for(auto v:e[u]) if(v.first!=f[u]){ f[v.first]=u; dfs(v.first); w[u]+=w[v.first]; }
}
void Dfs(int u)
{
	for(auto v:e[u]) if(v.first!=f[u])
	{
		if(!r.first||std::max(W-w[v.first],w[v.first])<std::max(W-w[r.second],w[r.second])) r={u,v.first};
		Dfs(v.first);
	}
}
piii a[N]; int A;
void _dfs(int u,int F)
{
	int x=u; E[u].clear(); t[c[u]][d[u]+W]++;
	while(x){ E[x].push_back(u); x=f[x]; }
	for(auto v:e[u]) if(v.first!=F)
	{
		f[v.first]=u; c[v.first]=c[u]; d[v.first]=d[u]+1; a[++A]={v.second,{u,v.first}};
		_dfs(v.first,u);
	}
}
void Add(i64 a,i64 b)
{
//	if(b) printf("+ %lld %lld\n",a,b);
	Ans+=b; ans+=a*b;
}
void solve(int x)
{
//	printf("%d\n",x);
	f[x]=0; dfs(x); W=w[x]; if(W==1) return ; r={0,0}; Dfs(x);
	int u=r.first,v=r.second; f[u]=f[v]=0; d[u]=d[v]=0; c[u]=0; c[v]=1; a[A=1]={e[u][v],{u,v}}; 
//	printf("%d %d\n",u,v);
	fr(i,0,W+W) t[0][i]=t[1][i]=0;
	_dfs(u,v); _dfs(v,u);
	std::sort(a+1,a+A+1); D=1;
//	fr(i,1,A) printf("%d  %d %d\n",a[i].first,a[i].second.first,a[i].second.second);
//	fr(i,0,W+W) printf("%d %d\n",t[0][i],t[1][i]);
	fr(i,1,A)
	{
//		printf("%d  %d %d\n",a[i].first,a[i].second.first,a[i].second.second);
		if(a[i].second==pii(u,v))
		{
//			fr(j,0,W+W) printf("%d%c",j==W,j==W+W?'\n':' ');
//			fr(T,0,1) fr(j,0,W+W) printf("%d%c",t[T][j],j==W+W?'\n':' ');
			fr(j,0,W+W) Add(a[i].first,(i64)t[0][j]*t[1][W+W-j]);
			D=-1; continue;
		}
		int x=a[i].second.first,y=a[i].second.second;
		for(auto j:E[y])
		{
			t[c[j]][d[j]+W]--; d[j]-=2; t[c[j]][d[j]+W]++;
//			printf("%d  %d\n",j,d[j]);
			Add(a[i].first,t[c[j]^1][W-(d[j]+1+D)]);
		}
	}
	e[u].erase(v); e[v].erase(u);
	solve(u); solve(v);
}
int main()
{
	freopen("hidden.in","r",stdin); freopen("hidden.out","w",stdout);
	n=read();
	fr(i,1,n-1){ int u=read(),v=read(),w=read(); e[u][v]=e[v][u]=w; }
	solve(1);
	printf("%.10lf\n",ans*1./Ans);
	return 0;
}
