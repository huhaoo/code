/***************************************************************
	File name: binary.cpp
	Author: huhao
	Create time: Wed 18 Nov 2020 10:49:15 AM CST
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
const int N=3000010;
int n,m;
char S[N],*s[N];
int l[N],p[N],id[N];
int c,t[N][2],f[N];
int e1[N],e2[N],_n;
std::vector<int> a[N];
std::vector<int> e[N],Id[N];
void Add(int u,int v){ e[u].push_back(v^1); e[v].push_back(u^1); }
int dfn[N],low[N],Dfn,_s[N],_t,IS[N];
void tarjan(int u)
{
	_s[++_t]=u; low[u]=dfn[u]=++Dfn; IS[u]=1;
	for(auto v:e[u])
		if(!dfn[v])
		{
			tarjan(v); low[u]=std::min(low[u],low[v]);
		}
		else if(IS[v]){ low[u]=std::min(low[u],dfn[v]); }
	if(dfn[u]==low[u])
	{
		id[u]=++m; Id[m].push_back(u);
		while(_s[_t]!=u){ id[_s[_t]]=m; Id[m].push_back(_s[_t]); IS[_s[_t]]=0; _t--; }
		IS[u]=0; _t--;
	}
}
int vis[N];
void dfs(int u)
{
	if(vis[u]) return ;
	vis[u]=1;
	for(auto i:e[u]) dfs(i);
}
int main()
{
	freopen("binary.in","r",stdin); freopen("binary.out","w",stdout);
	n=read();
	s[0]=S;
	fr(i,1,n)
	{
		s[i]=s[i-1]+l[i-1]+3;
		scanf("%s",s[i]+1); l[i]=strlen(s[i]+1);
		fr(j,1,l[i]) if(s[i][j]=='?') p[i]=j;
		fr(j,1,l[i]) s[i][j]-='0';
		id[i]=i;
	}
	std::sort(id+1,id+n+1,[&](int a,int b){ return l[a]<l[b]; });
	c=1; _n=n+n+1;
	fr(i,1,n) if(p[i]==0) e[i<<1|1].push_back(i<<1);
	fr(I,1,n) fr(j,0,p[id[I]]?1:0)
	{
		int i=id[I],Id=i<<1|j; s[i][p[i]]=j;
		int q=1;
		fr(j,1,l[i])
		{
			if(!t[q][s[i][j]]) f[t[q][s[i][j]]=++c]=q;
			q=t[q][s[i][j]];
		}
		a[q].push_back(Id);
	}
	fr(i,1,c)
	{
		e1[i]=++_n;
		for(auto j:a[i]) e[j].push_back(_n);
		e2[i]=++_n;
		for(auto j:a[i]) e[_n].push_back(j^1);
		int C=a[i].size();
		fr(j,0,C-1){ e[_n+j+1].push_back(a[i][j]^1); }
		fr(j,1,C-1) e[_n+j+1].push_back(_n+j);
		fr(j,0,C-1){ e[_n+C+j+1].push_back(a[i][j]^1); }
		fr(j,1,C-1) e[_n+C+j].push_back(_n+C+j+1);
		fr(j,0,C-1)
		{
			if(j!=0) e[a[i][j]].push_back(_n+j);
			if(j!=C-1) e[a[i][j]].push_back(_n+C+j+2);
		}
		_n+=C+C;
	}
	fr(i,1,c) for(auto j:a[i])
	{
		int u=f[i];
		while(u!=1){ e[e1[u]].push_back(j^1); e[j].push_back(e2[u]); u=f[u]; }
	}
/*	fr(i,2,n+n+1)
	{
		memset(vis,0,sizeof(vis));
		dfs(i);
		fr(j,2,n+n+1) if(vis[j]&&i!=j) printf("%d %d\n",i,j);
	}*/
//	fr(i,2,_n) for(auto j:e[i]) printf("%d %d\n",i,j);
	memset(id,0,sizeof(id));
	fr(i,2,_n) if(!dfn[i]) tarjan(i);
	static int d[N],q[N],_l,_r,_id[N];
	_l=1;
	fr(i,1,m) for(auto j:Id[i]) for(auto k:e[j]) if(id[k]!=i) d[id[k]]++;
	fr(i,1,m) if(!d[i]) q[++_r]=i;
	while(_l<=_r)
	{
		int i=q[_l++];
		for(auto j:Id[i]) for(auto k:e[j]) if(!(--d[id[k]])) q[++_r]=id[k];
	}
	fr(i,1,m) _id[q[i]]=i;
//	fr(i,2,n+n+1) printf("%d%c",id[i],i==end_i?'\n':' ');
	fr(i,1,n) if(_id[id[i<<1]]==_id[id[i<<1|1]]){ printf("NO\n"); return 0; }
	fr(i,1,n) if(_id[id[i<<1]]>_id[id[i<<1|1]]) s[i][p[i]]=0; else s[i][p[i]]=1;
	printf("YES\n");
	fr(i,1,n)
	{
		fr(j,1,l[i]) putchar(s[i][j]+'0');
		putchar(10);
	}
	return 0;
}
