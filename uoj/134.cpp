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
const int N=5010;
int u[N],v[N],w[N],d[N];
std::vector<int> e[N];
int p[N];
int n,m;
int id[N];
int s,t;
void dfs(int u)
{
	for(auto i:e[u]) if(!p[i]){ p[i]=u; dfs(i); }
}
int dfs(int S,int T)
{
	s=S; t=T; memset(p,0,sizeof(p)); p[t]=-1;
	fr(i,1,n) e[i].clear();
	fr(i,1,m)
	{
		if(!w[i]||d[i]==0) e[u[i]].push_back(v[i]);
		if(!w[i]||d[i]==1) e[v[i]].push_back(u[i]);
	}
	dfs(t); return p[s]!=0;
}
int main()
{
	n=read(); m=read();
	fr(i,1,m){ u[i]=read(); v[i]=read(); w[i]=read(); }
	while(n>1)
	{
		fr(i,1,m) if(u[i]!=v[i])
		{
			if(!w[i]){ w[i]=1; d[i]=0; if(dfs(u[i],v[i])) break; d[i]=1; if(dfs(v[i],u[i])) break; }
			else if(dfs(u[i],v[i])) break;
			assert(0);
		}
		static int a[N],A; a[A=1]=s;
		while(a[A]!=t){ A++; a[A]=p[a[A-1]]; }
		int _n=1; memset(id,0,sizeof(id)); fr(i,1,A) id[a[i]]=1; fr(i,1,n) if(id[i]!=1) id[i]=++_n;
		fr(i,1,m) if(!w[i]&&id[u[i]]==1&&id[v[i]]==1){ w[i]=1; d[i]=(p[u[i]]==v[i]); }
		fr(i,1,m){ u[i]=id[u[i]]; v[i]=id[v[i]]; }
		n=_n;
	}
	fr(i,1,m) printf("%d\n",d[i]);
	return 0;
}