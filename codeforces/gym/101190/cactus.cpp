/***************************************************************
	File name: cactus.cpp
	Author: huhao
	Create time: Wed 04 Nov 2020 08:32:20 PM CST
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
const int N=100010;
int n,s[N],t,dfn[N],T,m,f[N];
std::vector<int> e[N];
#define C(a,b,c) printf("c %d %d %d\n",a,b,c)
#define R(a,b,c) printf("r %d %d %d\n",a,b,c)
#define J(a,b) printf("j %d %d\n",a,b)
int Dfs(int u,int lst=0)
{
	f[u]=lst;
	dfn[u]=++T; m++; int p=0,q=0,r=0;
	std::vector<int> s1,s2,s3; static int P[N];
	for(auto v:e[u]) if(v!=lst)
	{
		if(!dfn[v]){ if(Dfs(v,u)){ s3.push_back(v); r=1; } else s2.push_back(v); }
		else if(dfn[v]>dfn[u])
		{
			int k=v;
			while(f[k]!=u) k=f[k];
			s1.push_back(k); P[k]=1; p=1;
		}
		else q=1;
	}
	for(auto i:s1) m++;
	if(p){ m+=2; }
	for(auto i:s3) m++;
	if(r) m++;
	for(auto i:s2) if(!P[i]) m++;
	m+=3;
	return q;
}

int dfs(int u,int lst=0)
{
	f[u]=lst;
	dfn[u]=++T; R(u,1,3); int p=0,q=0,r=0;
	std::vector<int> s1,s2,s3; static int P[N];
	for(auto v:e[u]) if(v!=lst)
	{
		if(!dfn[v]){ if(dfs(v,u)){ s3.push_back(v); r=1; } else s2.push_back(v); }
		else if(dfn[v]>dfn[u])
		{
			int k=v;
			while(f[k]!=u) k=f[k];
			s1.push_back(k); P[k]=1; p=1;
		}
		else q=1;
	}
	for(auto i:s1) J(u,i);
	if(p){ C(u,3,4); R(u,4,1); }
	for(auto i:s3) J(u,i);
	if(r) C(u,3,4);
	for(auto i:s2) if(!P[i]) J(u,i);
	C(u,2,3); R(u,2,1); R(u,3,q?4:2);
	return q;
}
void spj()
{
	fflush(stdout);
	fclose(stdin); fclose(stdout);
	freopen("cactus.out","r",stdin);
	static int id[N],c[N];
	fr(i,1,n){ id[i]=i; c[i]=1; }
	int m=read();
	fr(t,1,m)
	{
		char s=getchar();
		while(s!='r'&&s!='c'&&s!='j') s=getchar();
		if(s=='r')
		{
			int u=read(),c1=read(),c2=read();
			fr(i,1,n) if(id[i]==id[u]&&c[i]==c1) c[i]=c2;
		}
		else if(s=='j')
		{
			int u=read(),v=read(),I=id[v];
			fr(i,1,n) if(id[i]==I) id[i]=id[u];
		}
		else
		{
			int u=read(),c1=read(),c2=read();
			fr(i,1,n) fr(j,1,n) if(id[i]==id[u]&&id[j]==id[u]&&c[i]==c1&&c[j]==c2) fprintf(stderr,"%d %d (%d)\n",i,j,t);
			fr(i,1,n) fprintf(stderr,"%d%c",c[i],i==n?'\n':' ');
		}
	}
}
int main()
{
	freopen("cactus.in","r",stdin); freopen("cactus.out","w",stdout);
	n=read();
	fr(T,1,read())
	{
		static int a[N];
		int m=read();
		fr(i,1,m) a[i]=read();
		fr(i,2,m){ e[a[i]].push_back(a[i-1]); e[a[i-1]].push_back(a[i]); }
	}
	Dfs(1); T=0; memset(dfn,0,sizeof(dfn));
	printf("%d\n",m);
	dfs(1);
//	spj();
	return 0;
}
