#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
#include"keys.h"
#ifdef huhao
#include"grader.cpp"
#endif

#include<map>
#include<set>
const int N=600010;
int n;
int r[N];
int t[N],Id[N];
int id(int u){ return u==Id[u]?u:Id[u]=id(Id[u]); }
std::map<int,std::vector<int> > e[N];
std::set<int> k[N]; std::set<int> K[N];
std::vector<int> Ans[N];
int vis[N];
void merge(int u,int v)
{
	if(e[u].size()+k[u].size()<e[v].size()+k[v].size())
	{
		std::swap(e[u],e[v]); std::swap(k[u],k[v]); std::swap(K[u],K[v]);
	}
	for(auto i:k[v]) if(k[u].find(i)==k[u].end())
	{
		k[u].insert(i); if(e[u].find(i)!=e[u].end()) K[u].insert(i);
	}
	for(auto &i:e[v])
	{
		auto &_e=e[u][i.first];
		if(i.second.size()>_e.size()) std::swap(i.second,_e);
		for(auto j:i.second) _e.push_back(j);
		if(k[u].find(i.first)!=k[u].end()) K[u].insert(i.first);
	}
	K[v].clear(); k[v].clear(); e[v].clear();
}
void solve(int u)
{
	St:; // Loj's stack memory is too small.
	assert(u==id(u)); if(t[u]==-1) return ;
	while(!K[u].empty())
	{
		int c=*--K[u].end(); auto &E=e[u][c];
		while(!E.empty())
		{
			int v=id(*--E.end()); E.pop_back();
			if(v==u) continue;
			if(!t[v]){ t[u]=v; u=v; goto St; return ; }
			int w=v;
			while(w!=u&&t[w]>0&&!vis[w]) w=id(t[w]);
			assert(t[w]||u==w);
			if(t[w]==-1||vis[w]){ w=v; while(t[w]!=-1&&!vis[w]){ vis[w]=1; w=id(t[w]); } }
			if(w!=u){ t[u]=v; /*solve(_t(v));*/ return ; }
			for(int i=v;i!=u;i=id(t[i])) merge(u,i);
			for(int i=v;i!=u;i=id(t[i])) Id[id(i)]=u;
			goto St; solve(u); return ;
		}
		e[u].erase(c); K[u].erase(c);
	}
	t[u]=-1;
}
std::vector<int> find_reachable(std::vector<int> R, std::vector<int> u, std::vector<int> v, std::vector<int> w)
{
	n=R.size();
	std::vector<int> ans(n);
	fr(i,0,n-1) r[i+1]=R[i]+1;
	fr(i,0,u.size()-1)
	{
		e[u[i]+1][w[i]+1].push_back(v[i]+1);
		e[v[i]+1][w[i]+1].push_back(u[i]+1);
	}
	fr(i,1,n) Id[i]=i;
	fr(i,1,n){ k[i].insert(r[i]); if(e[i].find(r[i])!=e[i].end()) K[i].insert(r[i]); }
	fr(i,1,n) if(!t[i]) solve(i);
	fr(i,1,n) Ans[id(i)].push_back(i);
	int mi=n;
	fr(i,1,n) if(id(i)==i&&t[i]==-1) mi=std::min(mi,(int)Ans[i].size());
	fr(i,1,n) if(t[id(i)]==-1&&Ans[id(i)].size()==mi) ans[i-1]=1;
	return ans;
}