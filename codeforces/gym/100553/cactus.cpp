/***************************************************************
	File name: cactus.cpp
	Author: huhao
	Create time: Mon 28 Dec 2020 09:18:12 AM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<assert.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
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
#include<set>
const int N=1000010;
struct graph
{
	int s,t,n;
	std::vector<pii> e;
	graph(){ n=2; s=1; t=2; e={{1,2}}; }
};
graph &ss(graph &a,graph &b)
{
	int op=0;
	if(a.e.size()<b.e.size()){ std::swap(a,b); op=1; }
	static int id[N];
	fr(i,1,b.n)
		if(i==b.s) id[i]=a.s;
		else id[i]=++a.n;
	for(auto i:b.e) a.e.push_back({id[i.first],id[i.second]});
	if(op==1){ a.t=id[b.t]; }
	return a;
}
graph &st(graph &a,graph &b)
{
	static int id[N];
	fr(i,1,b.n)
		if(i==b.t) id[i]=a.s;
		else id[i]=++a.n;
	for(auto i:b.e) a.e.push_back({id[i.first],id[i.second]});
	a.s=id[b.s];
	return a;
}
graph &ts(graph &a,graph &b)
{
	if(a.e.size()<b.e.size()){ st(b,a); std::swap(a,b); return a; }
	static int id[N];
	fr(i,1,b.n)
		if(i==b.s) id[i]=a.t;
		else id[i]=++a.n;
	for(auto i:b.e) a.e.push_back({id[i.first],id[i.second]});
	a.t=id[b.t];
	return a;
}
graph &stts(graph &a,graph &b)
{
	int op=0;
	if(a.e.size()<b.e.size()){ op=1; std::swap(a,b); }
	static int id[N];
	fr(i,1,b.n)
		if(i==b.s) id[i]=a.t;
		else if(i==b.t) id[i]=a.s;
		else id[i]=++a.n;
	for(auto i:b.e) a.e.push_back({id[i.first],id[i.second]});
	if(op) std::swap(a.s,a.t);
	return a;
}
graph &c(std::vector<graph*> a)
{
	if(a.size()==1) return *(a[0]);
//*	for(auto i:a) printf("%d ",i->n);; putchar(10);
	fr(i,1,a.size()-1) ts(*(a[0]),*(a[i]));
//	printf("%d\n\n",a[0]->n);
	return *(a[0]);
}
graph &t(std::vector<graph*> a)
{
	if(a.size()==1) return *(a[0]);
	fr(i,1,a.size()-1) ss(*(a[0]),*(a[i]));
	return *(a[0]);
}
graph &loop(std::vector<graph*> a)
{
	if(a.size()==1) return *(a[0]);
	fr(i,2,a.size()-1) ts(*(a[1]),*(a[i]));
	stts(*(a[0]),*(a[1]));
	return *(a[0]);
}
char s[N]; int l; int p[N]; int v[N];
std::set<int> e[N]; int n;
std::vector<std::vector<int> > EE,E;
graph &solve(int);
int val(int &u)
{
	int r=0;
	if(s[u]>='0'&&s[u]<='9')
	{
		while(s[u]>='0'&&s[u]<='9'){ r=r*10+s[u]-48; u++; }
	}
	else r=v[s[u++]];
	return r;
}
std::vector<graph*> Solve(int u)
{
	std::vector<graph*> a;
	if(s[u]=='c'||s[u]=='t'||s[u]=='l')
	{
		while(1)
		{
			if(s[u]=='c'&&s[u+1]!='(')
			{
				a.push_back(new graph); u++;
			}
			else
			{
				a.push_back(&solve(u));
				u=p[(s[u]=='l'?u+4:u+1)]+1;
			}
			if(s[u]==',') u++;
			else break;
		}
	}
	else
	{
		int *q; int l,r;
		if(s[u]=='r')
		{
			q=&v[s[u+6]]; l=val(u+=8); r=val(++u); u++;
		}
		else
		{
			l=1; r=val(u); q=new int;
		}
		if(l>r) std::swap(l,r);
//		printf("%d %d\n",l,r); fflush(stdout);
		fr(i,l,r)
		{
			*q=i;
			if(s[u]==')') a.push_back(new graph);
			else a.push_back(&solve(u+1));
		}
	}
	return a;
}
graph &solve(int u)
{
//	printf("%d %c\n",u,s[u]); fflush(stdout);
	if(s[u]=='c'&&s[u+1]!='(') return *(new graph);
	if(s[u]=='c') return c(Solve(u+2));
	if(s[u]=='t') return t(Solve(u+2));
	if(s[u]=='l') return loop(Solve(u+5));
	assert(false);
}
void dfs(int u,std::vector<int> &E)
{
	E.push_back(u);
	if(e[u].empty()) return ;
	int v=*e[u].begin(); e[u].erase(v); e[v].erase(u); dfs(v,E);
}
int main()
{
	freopen("cactus.in","r",stdin); freopen("cactus.out","w",stdout);
	scanf("%s",s+1); l=strlen(s+1);
	static int a[N],A;
	fr(i,1,l)
		if(s[i]=='(') a[++A]=i;
		else if(s[i]==')'){ p[i]=a[A]; p[a[A]]=i; A--; }
	graph ans=solve(1); n=ans.n;
	static int id[N]; int m=2;
	fr(i,1,n)
		if(i==ans.s) id[i]=1;
		else if(i==ans.t) id[i]=n;
		else id[i]=m++;
/*	printf("%d %d %d\n",ans.n,ans.s,ans.t);
	for(auto i:ans.e) printf("%d %d\n",i.first,i.second);
	putchar(10);*/
	for(auto i:ans.e){ e[id[i.first]].insert(id[i.second]); e[id[i.second]].insert(id[i.first]); }
	fr(i,1,n) if(e[i].size()&1)
	{
		std::vector<int> p; dfs(i,p);
		EE.push_back(p);
	}
	for(auto i:EE)
	{
//		E.push_back(i); continue;
		std::vector<int> p=i,q;
		while(p.size())
		{
			int u=p[p.size()-1]; p.pop_back();
			if(e[u].size()) dfs(u,p);
			else q.push_back(u);
		}
		E.push_back(q);
	}
	fr(i,1,n) if(e[i].size())
	{
		std::vector<int> p={i},q;
		while(p.size())
		{
			int u=p[p.size()-1]; p.pop_back();
			if(e[u].size()) dfs(u,p);
			else q.push_back(u);
		}
		E.push_back(q);
	}
	printf("%d %d\n",n,E.size());
	for(auto i:E)
	{
		printf("%d",i.size());
		for(auto j:i) printf(" %d",j);
		putchar(10);
	}
	return 0;
}
