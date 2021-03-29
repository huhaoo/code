/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Wed 05 Aug 2020 03:54:58 PM CST
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
#define i64 long long
const int N=1000010,K=30,mod=998244353;
i64 power(i64 a,i64 b,i64 p=mod)
{
	i64 r=1;
	for(;b;b>>=1,a=a*a%p) if(b&1) r=r*a%p;
	return r;
}
i64 inv(i64 a){ return power(a,mod-2); }
namespace run
{
	int begin[N],next[N],to[N],e,n,m,k;
	void add(int u,int v){ e++; next[e]=begin[u]; begin[u]=e; to[e]=v; }
#define fo(i,a) for(int i=begin[a];i;i=next[i])
	int dfn[N],Dfn,low[N],s[N],t,_id[N];
	int id[N],Id;
	int vis[N]; i64 f[N][2];
	void Min(int &a,int b){ if(a>b) a=b; }
	int Mod(int a){ return a>=mod?a-mod:a; }
	void Add(int &a,int b){ a=Mod(a+b); }
	void tarjan(int u,int lst)
	{
		s[++t]=u; dfn[u]=low[u]=++Dfn;
		fo(i,u)
			if(!dfn[to[i]])
			{
				tarjan(to[i],u); Min(low[u],low[to[i]]);
			}
			else if(to[i]!=lst) Min(low[u],dfn[to[i]]);
		if(dfn[u]==low[u])
		{
			Id++; while(s[t]!=u) id[s[t--]]=Id;
			id[s[t--]]=Id;
		}
	}
	void solve(int u) ;
	void Solve(int u)
	{
		vis[u]=1; f[u][1]=1;
		fo(i,u)
			if(!vis[to[i]])
			{
				if(id[to[i]]==id[u]) Solve(to[i]);
				else
				{
					solve(to[i]);
					f[u][0]=((i64)f[u][0]*f[to[i]][0]+mod-(i64)f[u][1]*f[to[i]][1]%mod)%mod;
					f[u][1]=(i64)f[u][1]*f[to[i]][0]%mod;
				}
			}
	}
	void findid(int u)
	{
		vis[u]=2; s[_id[u]=++t]=u;
		fo(i,u) if(vis[to[i]]!=2&&id[to[i]]==id[u]) findid(to[i]);
	}
	i64 a[K][K];
	int calc(int n)
	{
		i64 ans=1;
		static i64 a[K][K];
		fr(i,1,n) fr(j,1,n) a[i][j]=::run::a[i][j];
		fr(i,1,n)
		{
			int p=i;
			while(!a[p][i]&&p<=n) p++;
			if(p>n) return 0;
			if(p!=i) ans=mod-ans;
			fr(j,i,n) std::swap(a[i][j],a[p][j]);
			i64 k=inv(a[i][i]); ans=ans*a[i][i]%mod;
			fr(j,i,n) a[i][j]=a[i][j]*k%mod;
			fr(j,i+1,n)
			{
				k=a[j][i];
				fr(l,i,n) a[j][l]=(a[j][l]-a[i][l]*k%mod+mod)%mod;
			}
		}
		return ans;
	}
	void solve(int u)
	{
		Solve(u); t=0; findid(u);
		fr(i,1,t) fr(j,1,t) a[i][j]=0;
		i64 F[2]={0,0};
		fr(i,1,t)
		{
			a[i][i]=f[s[i]][0];
			fo(j,s[i]) if(id[s[i]]==id[to[j]]) a[i][_id[to[j]]]=f[s[i]][1];
		}
		F[0]=calc(t);
		fr(i,1,t) a[1][i]=0;
		a[1][1]=f[u][1];
		F[1]=calc(t);
		f[u][0]=F[0]; f[u][1]=F[1];
	}
	int main()
	{
		n=read(); m=read(); k=read();
		fr(i,1,m){ int u=read(),v=read(); add(u,v); add(v,u); }
		tarjan(1,0); solve(1); printf("%lld\n",f[1][0]);
		return 0;
	}
}
int main(){ return run::main(); }
