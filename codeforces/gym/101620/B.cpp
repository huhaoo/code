/***************************************************************
	File name: B.cpp
	Author: huhao
	Create time: Wed 18 Nov 2020 04:42:44 PM CST
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
		if(c==EOF) exit(1);
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
#include<functional>
#include<set>
#define pii std::pair<int,int>
const int N=300010,M=1<<20|10,L=20;
int n,m;
int x[N],y[N];
int X[N],Y[N];
int a[N],A;
int f[N],ans[N],Ans[N],F[N][L+2];
std::vector<pii> e[N];
std::set<pii> s;
int vis[N];
void solve(int i)
{
	if(!i||vis[i]) return ;
	vis[i]=1; solve(f[i]);
	if(i<f[i])
	{
		int u=f[i];
		fd(j,L,0) if(F[u][j]>i) u=F[u][j];
//		printf("%d %d\n",u,i);
		f[i]=u>i?f[u]:u;
	}
	F[i][0]=f[i]; fr(j,1,L) F[i][j]=F[F[i][j-1]][j-1];
}
int main()
{
	m=read();
	fr(i,1,m){ x[i]=read(); y[i]=read(); }
	n=read();
	fr(i,1,n){ X[i]=read(); Y[i]=read(); }
	A=0;
	fr(i,1,n) a[++A]=X[i];
	std::sort(a+1,a+A+1); A=std::unique(a+1,a+A+1)-a-1;
	fr(i,1,n) X[i]=std::lower_bound(a+1,a+A+1,X[i])-a;
	fr(i,1,m) x[i]=std::lower_bound(a+1,a+A+1,x[i])-a;
	fr(i,1,n) e[X[i]].push_back(pii(Y[i],i));
	fr(i,1,m) e[x[i]].push_back(pii(y[i],0));
	s.insert(pii(1234567890,0));
	fd(i,n,1)
	{
		std::sort(e[i].begin(),e[i].end(),std::greater<pii>());
		for(auto u:e[i])
		{
			int p=s.lower_bound(pii(u.first,0))->second;
			if(u.second)
			{
				f[u.second]=p;
				auto it=s.insert(u).first;
				while(it!=s.begin())
				{
					it--; if(it->second>u.second) it=s.erase(it); else break;
				}
			}
			else ans[p]++;
		}
	}
//	fr(i,1,n) printf("%d%c",f[i],i==n?'\n':' ');
	fr(i,1,n) solve(i);
	fd(i,n,1) ans[f[i]]+=ans[i];
//	fr(i,1,n) printf("%d%c",f[i],i==n?'\n':' ');
	fr(i,1,n) printf("%d\n",ans[i]);
	return 0;
}
