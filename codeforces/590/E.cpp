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
const int N=1510,M=20000010;
int n;
char *a[N]; char A[M+N*10];
int s[M][2],f[M],m; int id[M],b[N];
std::bitset<N> e[N];
int E[N][N];
int p[N],vis[N];
int c[N];
int dfs(int u)
{
	if(vis[u]) return 0;; vis[u]=1;
	fr(v,1,n+n) if(E[u][v]&&!p[v]){ p[u]=v; p[v]=u; return 1; }
	fr(v,1,n+n) if(E[u][v]&&dfs(p[v])){ p[u]=v; p[v]=u; return 1; }
	return 0;
}
void choose(int u)
{
	c[u]=1;
	fr(v,1,n+n) if(E[u][v]&&p[v]&&!c[p[v]]) choose(p[v]);
}
int main()
{
	n=read(); m=1;
	a[1]=A;
	fr(i,1,n)
	{
		char *p=a[i];
		while(1){ *p=getchar(); if(*p<'a'||*p>'b') break; p++; }
		a[i+1]=p+2;
		
		int k=1;
		for(char *j=a[i];*j=='a'||*j=='b';j++){ if(!s[k][*j-'a']) s[k][*j-'a']=++m; k=s[k][*j-'a']; }
		if(!id[k]) id[k]=i; else b[i]=1;
	}
	std::queue<int> q;
	f[1]=1; fr(i,0,1) if(s[1][i]){ q.push(s[1][i]); f[s[1][i]]=1; } else s[1][i]=1;
	while(!q.empty())
	{
		int t=q.front(); q.pop(); if(!id[t]) id[t]=id[f[t]];
		fr(i,0,1) if(s[t][i]){ q.push(s[t][i]); f[s[t][i]]=s[f[t]][i]; } else s[t][i]=s[f[t]][i];
	}
	fr(i,1,n) if(!b[i])
	{
		int k=1;
		for(char *j=a[i];*j=='a'||*j=='b';j++){ k=s[k][*j-'a']; e[i][id[k]!=i?id[k]:id[f[k]]]=1; }
	}
	fr(k,1,n) fr(i,1,n) if(e[i][k]) e[i]|=e[k];
	fr(i,1,n) fr(j,1,n) if(e[i][j]) E[i+n][j]=E[j][i+n]=1;
	fr(i,1,n+n) if(!p[i]){ memset(vis,0,sizeof(vis)); dfs(i); }
//	fr(i,1,n+n) printf("%d%c",p[i],i==n+n?'\n':' ');
	fr(i,1,n+n) if(!b[i>n?i-n:i]&&!p[i]&&!c[i]) choose(i);
	fr(i,1,n+n) if(!b[i]&&!c[i]&&!c[p[i]]) choose(i);
//	fr(i,1,n+n) printf("%d%c",c[i],i==n+n?'\n':' ');
	std::vector<int> ans;
	fr(i,1,n) if(!b[i]&&c[i]&&c[i+n]) ans.push_back(i);
	printf("%d\n",ans.size());
	for(auto i:ans) printf("%d ",i);
	return 0;
}