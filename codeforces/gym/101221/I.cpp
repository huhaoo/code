/***************************************************************
	File name: I.cpp
	Author: huhao
	Create time: Fri 13 Nov 2020 04:51:36 PM CST
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
namespace solve
{
	const int N=110;
	int n,m,e[N][N];
	int p[N];
	int c[N],C[N];
	void init(int _n,int _m)
	{
		n=_n; m=_m;
		fr(i,1,n) fr(j,1,m) e[i][j]=0;
	}
	int vis[N];
	int dfs(int u,int op)
	{
		if(vis[u]) return 0;
		vis[u]=1;
		fr(i,1,m) if(e[u][i]&&(!p[i]||dfs(p[i],op)))
		{
			if(op) p[i]=u;
			return 1;
		}
		return 0;
	}
	int _dfs(int u,int op){ fr(i,1,n) vis[i]=0; return dfs(u,op); }
	void solve()
	{
		fr(i,1,m) p[i]=0;
		fr(i,1,n) _dfs(i,1);
		fr(i,1,n) c[i]=1;
		fr(i,1,m) C[i]=1;
		fr(i,1,m) if(p[i])
		{
			if(_dfs(p[i],0)) c[p[i]]=0;
			else C[i]=0;
		}
		fr(i,1,n) fr(j,1,m) assert(!(c[i]&&C[j]&&e[i][j]));
	}
}
const int N=110;
int n,d,x[N],y[N];
int D[N][N];
std::vector<int> ans;
int e[N][N],c[N],a[N],q;
void dfs(int u)
{
	fr(v,1,q) if(e[u][v]){ if(c[v]==2){ c[v]=c[u]^1; dfs(v); } else assert(c[u]!=c[v]); }
}
int main()
{
	n=read(); d=read(); d=d*d;
	fr(i,1,n){ x[i]=read(); y[i]=read(); }
	fr(i,1,n) fr(j,1,n){ D[i][j]=(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j]); }
	ans={1};
	fr(i,1,n) fr(j,i+1,n) if(D[i][j]<=d)
	{
		q=0;
		fr(k,1,n) if(k!=i&&k!=j&&D[i][j]>=D[i][k]&&D[i][j]>=D[k][j]) a[++q]=k;
		fr(k,1,q) fr(l,1,q) if(D[a[k]][a[l]]>d) e[k][l]=1; else e[k][l]=0;
//		printf("%d %d   %d\n",i,j,q);
//		fr(k,1,q) fr(l,1,q) printf("%d%c",e[k][l],l==q?'\n':' ');
		fr(k,1,q) c[k]=2;
		fr(k,1,q) if(c[k]==2){ c[k]=0; dfs(k); }
		int x=0,y=0; static int id[N];
		fr(k,1,q) if(c[k]==0) id[k]=++x; else id[k]=++y;
		solve::init(x,y);
		fr(k,1,q) if(c[k]==0) fr(l,1,q) if(c[l]==1&&e[k][l]) solve::e[id[k]][id[l]]=1;
		solve::solve();
		std::vector<int> Ans={i,j};
		fr(k,1,q) if((c[k]==0?solve::c:solve::C)[id[k]]) Ans.push_back(a[k]);
		if(Ans.size()>ans.size()) ans=Ans;
	}
	printf("%d\n",ans.size());
	fr(i,0,ans.size()-1) printf("%d%c",ans[i],i==end_i?'\n':' ');
	return 0;
}
