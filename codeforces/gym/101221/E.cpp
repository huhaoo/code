/***************************************************************
	File name: E.cpp
	Author: huhao
	Create time: Mon 28 Dec 2020 08:26:22 PM CST
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
#include<vector>
#include<map>
const int N=110;
int t[N][N],n,m,f[N],p[N],st[N];
std::vector<int> F[N],g[N];
std::vector<int> Ans[N];
std::map<std::vector<int>,int> T;
std::vector<std::vector<int> > ans;
int main()
{
	n=read();
	fr(i,1,n) fr(j,1,t[i][0]=read()) t[i][j]=read();
	fr(q,1,n)
	{
		fr(i,1,n){ p[i]=-1; F[i].clear(); g[i].clear(); }
		int op=0;
		fr(i,1,n)
		{
			static std::vector<int> v[N];
			fr(j,1,t[i][0])
			{
				std::vector<int> a;
				fr(k,1,t[i][0]) a.push_back(f[t[i][(j+k-2)%t[i][0]+1]]);
				if(F[i].empty()||a<F[i]){ st[i]=j; F[i]=a; }
				v[j]=a;
			}
			if(op) continue;
			int o=t[i][0];
			fr(j,2,t[i][0]) if(v[j]==v[1]){ o=j-1; break; }
//			printf("%d %d\n",i,o);
			fr(j,1,o) fr(k,j+1,o) if(f[t[i][j]]==f[t[i][k]]) op=f[i]<<10|o;
		}
		static std::vector<int> lst[N];
		fr(i,1,m) lst[i].clear();
		fr(i,1,n)
		{
			if(lst[f[i]].empty()) lst[f[i]]=F[i];
			if(lst[f[i]]!=F[i]) op=0;
		}
		if(op)
		{
			int u=op&1023,v=op>>10;
			fr(i,1,n) if(f[i]==v) fr(j,1,u) g[t[i][(j-2+st[i])%t[i][0]+1]].push_back(j);
		}
		T.clear(); m=0;
/*		printf("%d\n",op);
		fr(i,1,n) printf("%d%c",f[i],i==n?'\n':' ');
		fr(i,1,n) fr(j,0,F[i].size()-1) printf("%d%c",F[i][j],j==end_j?'\n':' ');
		putchar(10);*/
		fr(i,1,n) std::sort(g[i].begin(),g[i].end());
		fr(i,1,n){ F[i].push_back(-1-f[i]); for(auto j:g[i]) F[i].push_back(j); }
		fr(i,1,n)
		{
			if(!T[F[i]]) T[F[i]]=++m;
			f[i]=T[F[i]];
		}
	}
	fr(i,1,n) Ans[f[i]].push_back(i);
	fr(i,1,m) if(Ans[i].size()>1) ans.push_back(Ans[i]);
	std::sort(ans.begin(),ans.end());
	for(auto i:ans) fr(j,0,i.size()-1) printf("%d%c",i[j],j==end_j?'\n':' ');
	if(ans.empty()) printf("none\n");
	return 0;
}
