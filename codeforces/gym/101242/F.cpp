/***************************************************************
	File name: F.cpp
	Author: huhao
	Create time: Fri 20 Nov 2020 09:42:52 PM CST
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
#define pii std::pair<int,int>
#include<vector>
#define i64 long long
const int N=1<<20|10,M=1<<22|10;
int n,m;
std::vector<pii> e[N];
i64 mi[N],d[N],L[N],R[N];
char name[N][15];
int b[M],c;
i64 a[M];
int ans[N];
void dfs(int u)
{
	if(u>n){ mi[u]=d[u]; return ; }
	mi[u]=1ll<<60;
	for(auto i:e[u])
	{
		d[i.first]=d[u]+i.second;
		dfs(i.first);
		R[i.first]=mi[i.first]-d[u]-1; mi[u]=std::min(mi[u],mi[i.first]); L[u]=std::max(L[u],std::max(R[i.first],L[i.first]));
	}
}
void add(int u,int v){ /*printf("+ %d %d\n",u,v);*/ for(;u;u&=u-1) b[u]+=v; }
int query(int u){ int ans=0; /*printf("Q %d => ",u);*/ for(;u<=c;u+=u&(-u)) ans+=b[u]; /*printf("%d\n",ans);*/ return ans; }
void solve(int u)
{
	if(u>n)
	{
		ans[u]=query(d[u]);
		return ;
	}
	add(L[u],1); add(R[u],-1);
	for(auto i:e[u]) solve(i.first);
	add(L[u],-1); add(R[u],1);
}
int main()
{
	m=read(); n=read();
	fr(i,n+1,n+m)
	{
		scanf("%s",name[i]);
		int f=read(),d=read();
		e[f].push_back({i,d});
	}
	fr(i,1,n)
	{
		int f=read(),d=read();
		e[f].push_back({i,d});
	}
	dfs(0);
	fr(i,0,n+m) L[i]=std::min(L[i],R[i]);
	fr(i,n+1,n+m) a[++c]=d[i];
	fr(i,0,n+m){ a[++c]=L[i]; a[++c]=R[i]; }
	std::sort(a+1,a+c+1);
//	fr(i,n+1,n+m) printf("%lld%c",d[i],i==end_i?'\n':' ');
//	fr(i,1,n+m) printf("%lld %lld\n",L[i],R[i]);
#define query(x) std::lower_bound(a+1,a+c+1,x)-a
	fr(i,n+1,n+m) d[i]=query(d[i]);
	fr(i,0,n+m){ L[i]=query(L[i]); R[i]=query(R[i]); }
#undef query
//	fr(i,n+1,n+m) printf("%lld%c",d[i],i==end_i?'\n':' ');
//	fr(i,0,n+m) printf("%lld %lld\n",L[i],R[i]);
	fr(i,0,n+m){ add(L[i],-1); add(R[i],1); }
	solve(0);
	fr(i,n+1,n+m) printf("%s %d\n",name[i],ans[i]+1);
	return 0;
}
