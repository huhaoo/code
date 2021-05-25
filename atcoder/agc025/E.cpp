/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Tue 20 Apr 2021 10:07:44 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define i64 long long
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
#define pii std::pair<int,int>
#define F first
#define S second
void swap(pii &a){ std::swap(a.F,a.S); }
int vis[2010];
int dfs(std::vector<std::vector<int> > &e,int s,int t)
{
	vis[s]|=1; if(s==t) return 1;
	for(auto i:e[s]) if(!(vis[i]&1)&&dfs(e,i,t)) return 1;
	vis[s]&=(~1); return 0;
}
int solve(std::vector<pii> e,std::vector<pii> &E)
{
	int n=e.size()+1,m=E.size();
	if(n<=2)
	{
		if(m>=2)
		{
			if(E[0]==E[1]) std::swap(E[1].F,E[1].S);
			return 2;
		}
		return m;
	}
	std::vector<std::vector<int> > t(n);
	for(auto i:e){ t[i.F].push_back(i.S); t[i.S].push_back(i.F); }
	int r=0;
	fr(i,0,n-1) if(t[i].size()==1) r=i;
	for(auto &i:E) if(i.S==r) swap(i);
	int x=-1,y=-1;
	for(auto i:E) if(i.F==r){ if(x==-1) x=i.S; else if(y==-1) y=i.S; }
	std::vector<int> id(n); int q=0; std::vector<pii> _e,_E;
	if(y==-1)
	{
		int F=t[r][0];
		fr(i,0,n-1) if(i!=r) id[i]=q++;
		for(auto i:e) if(i.F!=r&&i.S!=r) _e.push_back({id[i.F],id[i.S]});
		for(auto i:E) if(i.F!=r) _E.push_back({id[i.F],id[i.S]});
		else if(i.S!=F) _E.push_back({id[F],id[i.S]});
		q=0; int ans=solve(_e,_E);
		for(auto &i:E) if(i.F!=r){ if(_E[q++]!=pii{id[i.F],id[i.S]}) swap(i); }
		else{ ans++; if(i.S!=F){ if(_E[q++]!=pii{id[F],id[i.S]}) swap(i); } }
		return ans;
	}
	memset(vis,0,sizeof(vis)); assert(dfs(t,r,x)); fr(i,0,n-1) vis[i]<<=1; assert(dfs(t,r,y));
	int ans=-2; q=1; fr(i,0,n-1) if(vis[i]!=3) id[i]=q++; else ans+=2;
	if(x!=y) _E.push_back({id[x],id[y]});
	for(auto i:e) if(id[i.F]!=id[i.S]) _e.push_back({id[i.F],id[i.S]});
	int X=1,Y=1;
	for(auto i:E) if((!X||i.F!=r||i.S!=x)&&(!Y||i.F!=r||i.S!=y)&&id[i.F]!=id[i.S]) _E.push_back({id[i.F],id[i.S]});
	else if(X&&i.F==r&&i.S==x) X=0; else if(Y&&i.F==r&&i.S==y) Y=0;
	ans+=solve(_e,_E); q=(x!=y?1:0); X=Y=1;
	for(auto &i:E) if((!X||i.F!=r||i.S!=x)&&(!Y||i.F!=r||i.S!=y)&&id[i.F]!=id[i.S]){ if(_E[q++]!=pii{id[i.F],id[i.S]}) swap(i); }
	else if(X&&i.F==r&&i.S==x)
	{
		if(x==y) ;
		else if(_E[0]==pii{id[x],id[y]}) swap(i);
		X=0;
	}
	else if(Y&&i.F==r&&i.S==y)
	{
		if(x==y) swap(i);
		else if(_E[0]==pii{id[y],id[x]}) swap(i);
		Y=0;
	}
	return ans;
}
int main()
{
	int n=read(),m=read();
	std::vector<pii> e,E;
	fr(i,1,n-1) e.push_back({read()-1,read()-1});
	fr(i,1,m) E.push_back({read()-1,read()-1});
	printf("%d\n",solve(e,E));
	for(auto i:E) printf("%d %d\n",i.F+1,i.S+1);
	return 0;
}
