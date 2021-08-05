#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
int read()
{
	int r=0,t=1,c=getchar();
	while(c<'0'||c>'9'){ t=c=='-'?-1:1; c=getchar(); }
	while(c>='0'&&c<='9'){ r=(r<<3)+(r<<1)+(c^48); c=getchar(); }
	return r*t;
}
const int N=100010;
int n,a[N];
std::vector<int> e[N];
int w[N],c[N],f[N];
void Dfs(int u)
{
	w[u]=a[u]; c[u]=1;
	for(auto v:e[u]){ Dfs(v); w[u]=std::max(w[u],w[v]); c[u]+=c[v]; }
	f[u]=a[u]-c[u]+1; std::sort(e[u].begin(),e[u].end(),[&](int u,int v){ return f[u]<f[v]; });
	int F=1;
	for(auto v:e[u]){ f[u]=std::max(f[u],f[v]-F); F+=c[v]; }
}
std::set<int> s; int ans[N],p;
void dfs(int u)
{
//	printf("%d:  ",u); for(auto v:e[u]) printf("%d ",v);; putchar(10);
	s.insert(a[u]); //std::reverse(e[u].begin(),e[u].end());
	while(!e[u].empty())
	{
		int v=e[u].back(); e[u].pop_back();
		dfs(v);
	}
	if(!s.count(p)){ printf("-1\n"); exit(0); }
	ans[u]=p; s.erase(p); p--;
}
int main()
{
	int op=read();
	n=read();
	fr(i,1,n) a[i]=read();
	fr(i,2,n) e[read()].push_back(i);
	Dfs(1); p=n; dfs(1);
	fr(i,1,n) printf("%d%c",ans[i],i==n?'\n':' ');
	return 0;
}