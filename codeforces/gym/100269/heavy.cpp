/***************************************************************
	File name: heavy.cpp
	Author: huhao
	Create time: Sun 01 Nov 2020 03:53:45 PM CST
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
#include<map>
#define i64 long long
#define pii std::pair<i64,i64>
const int N=5010,M=N*550;
const int s1=10007,m1=998244353,s2=12345,m2=1000000007;
struct trie
{
	int id[M],n;
	std::map<pii,int> t;
	int insert(char *s,int m)
	{
		pii a;
		fr(i,1,m){ a.first=(a.first*s1+s[i])%m1; a.second=(a.second*s2+s[i])%m2; }
		if(!t.count(a)) t[a]=++n;
		return t[a];
	}
} t1,t2;
std::vector<int> e[N],E[N],p1[N],p2[N];
int n,k,vis[N],p[N],_p[N];
int dfs(int u,int op=1)
{
	if(vis[u]) return 0;
	vis[u]=1;
	for(auto i:e[u]) if(!p[i]||dfs(p[i],op)){ if(op) p[i]=u; return 1; }
	return 0;
}
int a[N],b[N];
int ans[N][N],Ans;
int main()
{
	freopen("heavy.in","r",stdin); freopen("heavy.out","w",stdout);
	n=read(); k=read();
	fr(i,1,n)
	{
		static char s[N];
		scanf("%s",s+1); int m=strlen(s+1);
		int a=t1.insert(s,k); std::reverse(s+1,s+m+1);
		int b=t2.insert(s,k);
		e[a].push_back(b); E[b].push_back(a); p1[a].push_back(i); p2[b].push_back(i);
		::a[i]=a; ::b[i]=b;
	}
	fr(i,1,n){ memset(vis,0,sizeof(vis)); dfs(i); }
	fr(i,1,n) if(p[i]){ memset(vis,0,sizeof(vis)); if(dfs(p[i],0)) _p[i]=0; else _p[i]=1; }
	memset(vis,0,sizeof(vis));
	fr(i,1,n) if(p[i])
	{
		static int s[N],t; t=0;
		for(auto j:(_p[i]?p2[i]:p1[p[i]])) if(!vis[j]){ vis[j]=1; s[++t]=j; }
		if(t)
		{
			Ans++; ans[Ans][0]=t; fr(i,1,t) ans[Ans][i]=s[i];
		}
	}
	printf("%d\n",Ans);
	fr(i,1,Ans)
	{
		printf("%d ",ans[i][0]);
		fr(j,1,ans[i][0]) printf("%d%c",ans[i][j],j==end_j?'\n':' ');
	}
	fr(i,1,n) assert(vis[i]);
	return 0;
}
