/***************************************************************
	File name: cactus.cpp
	Author: huhao
	Create time: Mon 02 Nov 2020 04:16:21 PM CST
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
#include<random>
#include<map>
const int N=200010,mod=998244353;
int n,m;
std::vector<int> e[N],E[N];
int dfn[N],low[N],Dfn,id[N],_f[N];
void add(std::vector<int> *e,int u,int v){ e[u].push_back(v); e[v].push_back(u); }
void tarjan(int u,int lst=0)
{
	dfn[u]=low[u]=++Dfn; _f[u]=lst;
	for(auto v:E[u]) if(v!=lst)
	{
		if(!dfn[v]){ tarjan(v,u); low[u]=std::min(low[u],low[v]); }
		else if(dfn[v]<low[u])
		{
			low[u]=dfn[v]; m++; add(e,m,v);
			int p=u;
			while(p!=v){ add(e,m,p); p=_f[p]; }
		}
	}
	if(dfn[u]==low[u]&&lst) add(e,u,lst);
}
int w[N],rt,mi;
void dfs(int u,int lst=0)
{
	w[u]=(u<=n); int mx=0; _f[u]=lst;
	for(auto v:e[u]) if(v!=lst){ dfs(v,u); w[u]+=w[v]; mx=std::max(mx,w[v]); }
	if(std::max(mx,n-w[u])<mi){ rt=u; mi=std::max(mx,n-w[u]); }
}
#define uint unsigned int
#define i64 long long
std::mt19937 Rand(123456789);
#define rand Rand
uint h[N];
void rotate(int u,int lst)
{
	for(auto v:e[u]) if(v!=lst) rotate(v,u);
	if(u>n&&u<=m)
	{
		int p=0;
		fr(i,0,e[u].size()-1) if(e[u][i]==lst) p=i;
		e[u].insert(e[u].end(),e[u].begin(),e[u].begin()+p);
		e[u].erase(e[u].begin(),e[u].begin()+p);
	}
}
std::map<int,int> ans;
void Add(int u,int info=0)
{
//	if(u>1&&info) printf("* %d  %d(%d)\n",u,info,e[info].size());
	fr(i,2,sqrt(u)+1) if(u%i==0)
	{
		while(u%i==0){ u/=i; ans[i]++; }
	}
	if(u>1) ans[u]++;
}
namespace bf
{
	const int N=110;
	int n,e[N][N],p[N];
	int main()
	{
		n=read();
		fr(i,1,read())
		{
			int k=read();
			static int a[N];
			fr(j,1,k) a[j]=read();
			fr(j,2,k) e[a[j]][a[j-1]]=e[a[j-1]][a[j]]=1;
		}
		fr(i,1,n) p[i]=i;
		int Ans=0;
		do
		{
			int flag=1;
			fr(i,1,n) fr(j,1,n) if(e[i][j]&&!e[p[i]][p[j]]) flag=0;
			Ans+=flag;
		}
		while(std::next_permutation(p+1,p+n+1));
		Add(Ans);
		printf("%d\n",ans.size());
		for(auto i:ans) printf("%d %d\n",i.first,i.second);
		return 0;
	}
}
std::map<std::vector<uint>,uint> _h; uint T;
void solve(int u,int lst)
{
	int l=e[u].size();
	static uint a[N]; int t=0,v=0;
	fr(i,0,e[u].size()-1) if((v=e[u][i])!=lst) solve(v,u);
	t=0;
	fr(i,0,e[u].size()-1) if((v=e[u][i])!=lst){ h[u]+=h[v]; a[++t]=h[v]; }
	if(u<=n||u==m+1)
	{
		std::sort(a+1,a+t+1);
		for(int x=1,y;x<=t;x=y+1)
		{
			y=x; while(y<t&&a[y+1]==a[x]) y++;
			fr(j,1,y-x+1) Add(j,u);
		}
	}
	else
	{
		int flag=1;
		fr(i,1,t) if(a[i]!=a[t-i+1]) flag=0;
		if(flag) Add(2,u);
	}
//	printf(" %d %d\n",u,t);
	std::vector<uint> A;
	fr(i,1,t) A.push_back(a[i]);
	if(u>n&&u<=m)
	{
		std::vector<uint> B=A; std::reverse(B.begin(),B.end());
		A=std::min(A,B); A.push_back(-1);
	}
	if(!_h.count(A)) _h[A]=++T;
	h[u]=_h[A];
}
int main()
{
	freopen("cactus.in","r",stdin); freopen("cactus.out","w",stdout);
//	return bf::main();
	n=read(); m=read();
	fr(i,1,m)
	{
		int k=read();
		static int a[N];
		fr(j,1,k) a[j]=read();
		fr(j,2,k) add(E,a[j],a[j-1]);
	}
	m=n; tarjan(1);
	fr(i,n+1,m) std::sort(e[i].begin(),e[i].end(),[&](int x,int y){ return dfn[x]<dfn[y]; });
	mi=n; dfs(1);
	if(rt<=n&&w[rt]*2==n&&_f[rt]<=n)
	{
		int Rt=_f[rt]; add(e,m+1,rt); add(e,m+1,Rt);
		e[rt].erase(std::find(e[rt].begin(),e[rt].end(),Rt));
		e[Rt].erase(std::find(e[Rt].begin(),e[Rt].end(),rt));
		rt=m+1;
	}
//	printf("%d\n",rt);
//	printf("%d %d\n",n,m);
/*	fr(i,1,m)
	{
		printf("%d:",i);
		for(auto j:e[i]) printf(" %d",j);
		putchar(10);
	}*/
	rotate(rt,0);
	if(rt==m+1||rt<=n) solve(rt,0);
	else
	{
		for(auto i:e[rt]) solve(i,rt);
		static uint s[N]; int l=0;
		for(auto i:e[rt]) s[++l]=h[i];
		static i64 a[N],p[N],A; static int sed=10007;
		p[0]=1;
		fr(i,1,l+l) p[i]=p[i-1]*sed%mod;
		fr(i,1,l+l) a[i]=(a[i-1]+s[i>l?i-l:i]%mod*p[i])%mod;
		A=a[l];
		int c=0;
		fr(i,l,l+l-1) if(A*p[l]%mod==(a[i]-a[i-l]+mod)*p[l+l-i]%mod) c++;
		std::reverse(s+1,s+l+1);
		fr(i,1,l+l) a[i]=(a[i-1]+s[i>l?i-l:i]%mod*p[i])%mod;
		fr(i,l,l+l-1) if(A*p[l]%mod==(a[i]-a[i-l]+mod)*p[l+l-i]%mod) c++;
		Add(c);
	}
//	fr(i,1,m) printf("%u%c",h[i],i==m?'\n':' ');
	printf("%d\n",ans.size());
	for(auto i:ans) printf("%d %d\n",i.first,i.second);
	return 0;
}
