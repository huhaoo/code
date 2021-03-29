/***************************************************************
	File name: gangsters.cpp
	Author: huhao
	Create time: Tue 17 Nov 2020 10:17:51 AM CST
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
#include<set>
#include<vector>
const int N=100010,L=20;
int n,q,f[N][L+2],dfn[N],w[N],Dfn,F[N],ans,W[N],Ans,_ans[N],id[N];
std::vector<int> e[N];
void dfs(int u)
{
	id[dfn[u]=++Dfn]=u; w[u]=1;
	for(auto i:e[u]){ dfs(i); w[u]+=w[i]; W[u]+=W[i]; }
	if(!W[u]) W[u]=1;
}
int b[N];
void modify(int p,int v){ /*printf("+ %d %d\n",p,v);*/ for(;p;p-=p&(-p)) b[p]+=v; }
int query(int p){ int ans=0,P=p; for(;p<=n;p+=p&(-p)) ans+=b[p]; /*printf("Q %d=> %d\n",P,ans);*/ return ans; }
int Query(int p){ return query(dfn[p])-query(dfn[p]+w[p]); }
void calc(int u)
{
	int s=Query(F[u]);
	if(!s){ _ans[F[u]]=0; return ; }
	int p=u;
	fd(i,L,0) if(f[p][i]!=0&&f[p][i]!=1&&Query(f[p][i])!=s) p=f[p][i];
	if(Query(p)!=s) p=f[p][0];
	_ans[F[u]]=W[p];
}
std::set<int> s;
int main()
{
	freopen("gangsters.in","r",stdin); freopen("gangsters.out","w",stdout);
	n=read(); q=read();
	fr(i,2,n)
	{
		e[f[i][0]=read()].push_back(i);
		if(f[i][0]==1) F[i]=i;
		else F[i]=F[f[i][0]];
	}
	dfs(1);
/*	fr(i,1,n) printf("%d%c",dfn[i],i==n?'\n':' ');
	fr(i,1,n) printf("%d%c",F[i],i==n?'\n':' ');
	fr(i,1,n) printf("%d%c",w[i],i==n?'\n':' ');
	fr(i,1,n) printf("%d%c",W[i],i==n?'\n':' ');*/
	fr(j,1,L) fr(i,1,n) f[i][j]=f[f[i][j-1]][j-1];
	while(q--)
	{
		char c=0;
		while(c!='+'&&c!='-') c=getchar();
		int p=read();
//		fprintf(stderr,"%c %d\n",c,p);
		ans-=_ans[F[p]];
		if(c=='+')
		{
			modify(dfn[p],1); s.insert(dfn[p]);
			calc(p);
		}
		else
		{
			modify(dfn[p],-1); s.erase(dfn[p]);
			if(Query(F[p])==0) _ans[F[p]]=0;
			else calc(id[*s.lower_bound(dfn[F[p]])]);
		}
		ans+=_ans[F[p]];
		if(c=='+'){ if(Query(F[p])==1) Ans++; }
		else{ if(Query(F[p])==0) Ans--; }
		printf("%d %d\n",Ans,ans-query(1));
//		printf("%d\n",Query(F[p]));
	}
	return 0;
}
