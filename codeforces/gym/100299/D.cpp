/***************************************************************
	File name: D.cpp
	Author: huhao
	Create time: Wed 18 Nov 2020 09:04:17 PM CST
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
#include<map>
#include<string>
#include<vector>
#include<iostream>
#include<queue>
#define pii std::pair<int,int>
#define piii std::pair<pii,int>
const int N=1000010;
std::string input(int T=1)
{
	std::string s;
	fr(i,1,T-1) std::cin>>s;
	std::cin>>s; return s;
}
std::vector<std::string> Input()
{
	std::vector<std::string> c;
	while(1)
	{
		auto s=input();
		if(*(--s.end())==',')
		{
			s.erase(--s.end());
			c.push_back(s);
		}
		else{ c.push_back(s); return c; }
	}
}
int n,m,s,t;
std::map<std::string,int> id;
std::vector<piii> e[N];
pii d[N];
int vis[N];
std::priority_queue<piii> q;
pii operator+(pii a,pii b){ return pii(a.first+b.first,a.second+b.second); }
int main()
{
	fr(T,1,read())
	{
		input(); n=0; id.clear();
		auto S=Input();
		fr(i,1,n=S.size()) id[S[i-1]]=i;
		input(); m=Input().size();
		fr(i,1,n) e[i].clear();
		fr(i,1,m)
		{
			input(2);
			auto _e=Input();
			std::vector<int> E;
			for(auto j:_e) E.push_back(id[j]);
			static int a[N]; int l=E.size();
			fr(i,0,l-1) e[a[i]=++n].clear();
#define Add(u,v,w,x) e[u].push_back({{w,x},v})
			fr(i,0,l-1) Add(a[i],E[i],0,0);
			fr(i,1,l-1){ Add(a[i],a[i-1],0,-1); Add(a[i-1],a[i],0,-1); }
			fr(i,0,l-1){ Add(E[i],a[0],-1,i); Add(E[i],a[l-1],-1,l-1-i); }
		}
		auto _s=input(4),_t=input(4); s=id[_s]; t=id[_t];
		std::cout<<"optimal travel from "<<_s<<" to "<<_t<<": ";
		fr(i,1,n){ vis[i]=0; d[i]={-N,0}; }
		d[s]=pii(0,0); q.push({d[s],s});
		while(!q.empty())
		{
			int u=q.top().second; q.pop();
			if(vis[u]) continue;
			vis[u]=1;
			for(auto v:e[u]) if(d[u]+v.first>d[v.second]){ d[v.second]=d[u]+v.first; q.push({d[v.second],v.second}); }
		}
		printf("%d line%s, %d minute%s\n",-d[t].first,d[t].first<-1?"s":"",d[t].second,d[t].second>1?"s":"");
	}
	return 0;
}
