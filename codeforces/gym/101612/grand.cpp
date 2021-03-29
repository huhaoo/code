/***************************************************************
	File name: grand.cpp
	Author: huhao
	Create time: Fri 20 Nov 2020 03:43:52 PM CST
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
#include<set>
#define i64 long long
const int N=100010;
int n,f[N],flag,vis[N],Vis[N],R[N];
std::vector<int> e[N];
void print(std::vector<int> E)
{
	printf("%d",E.size());
	for(auto i:E) printf(" %d",i);
	putchar(10);
}
void dfs(int u)
{
	if(flag) return ;
//	printf("%d %d\n",u,f[u]);
	vis[u]=Vis[u]=1;
	for(auto v:e[u]) if(!Vis[v]){ f[v]=u; dfs(v); }
	if(flag) return ;
	for(auto v:e[u]) if(v!=f[u]&&vis[v])
	{
		static int a[N]; int c;
		a[c=1]=u;
		while(a[c]!=v){ a[c+1]=f[a[c]]; c++; }
//		fprintf(stderr,"%d\n",c);
//		fr(i,1,c) fprintf(stderr,"%d%c",a[i],i==c?'\n':' ');
		fr(i,1,c-1) if(R[a[i]])
		{
			int j=i;
			while(j<c-1&&R[a[j+1]]==R[a[j]]) j++;
			printf("%d %d\n",a[i],a[j+1]);
			if(j==c-1)
			{
				int k=a[j];
				while(R[f[k]]==R[k]) k=f[k];
				i=a[i]; j=a[j+1]; int _k=k; k=f[k]; int l=a[1];
				int u=i,v=j; std::vector<int> A={u};
				while(u!=v) A.push_back(u=f[u]);
				print(A);
				u=l; v=i; A={j,l};
				while(u!=v) A.push_back(u=f[u]);
				std::reverse(A.begin(),A.end()); print(A);
				
				u=j; v=k; A={u};
				while(u!=v) A.push_back(u=f[u]);
				u=R[_k]; v=i; A.push_back(u);
				while(u!=v) A.push_back(u=f[u]);
				std::reverse(A.begin(),A.end()); print(A);
			}
			else
			{
				std::vector<int> A;
				A.clear();
				fr(k,i,j+1) A.push_back(a[k]);
				print(A);
				A.clear();
				fd(k,i,1) A.push_back(a[k]);
				fd(k,c,j+1) A.push_back(a[k]);
				print(A);
				A.clear(); A={a[j+1]};
				int u=R[a[j]],v=a[i]; A.push_back(u);
				while(u!=v) A.push_back(u=f[u]);
				std::reverse(A.begin(),A.end()); print(A);
			}
			flag=1; return ;
		}
		fr(i,1,c-1) R[a[i]]=u;
	}
	vis[u]=0;
}
int main()
{
	freopen("grand.in","r",stdin); freopen("grand.out","w",stdout);
	fr(T,1,read())
	{
//		printf(" %d\n",T);
		n=read(); flag=0;
		fr(i,1,n){ vis[i]=Vis[i]=R[i]=0; e[i].clear(); }
		fr(i,1,read())
		{
			int u=read(),v=read();
			e[u].push_back(v); e[v].push_back(u);
//			printf("%d %d\n",u,v);
		}
		fr(i,1,n) if(!Vis[i]){ f[i]=0; dfs(i); }
		if(!flag) printf("-1\n");
		fflush(stdout);
	}
	return 0;
}
