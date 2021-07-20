#include<stdio.h>
#include<algorithm>
#include<string.h>
#include<vector>
#include<time.h>
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
const int N=410,M=640010;
int n,m;
char s[N][N];
std::vector<int> e[M],E[M];
int d[M];
int q[M<<3],l,r;
void Add(int u,int v){ e[u].push_back(v); E[v].push_back(u); }
int ans[M],p[M];
int vis[M];
int Ans;
void dfs(int u,int p)
{
	if(Ans==M||!::p[u*2+p]){ Ans=M; return ;; } q[l=r=1]=u*2+p;
	while(l<=r)
	{
		u=q[l++]; if(vis[u>>1]!=-1){ if(vis[u>>1]!=(u&1)){ Ans=M; return ; } continue; } vis[u>>1]=u&1; Ans++;
		for(auto i:e[u]) q[++r]=i;
	}
}
char Out[1<<22],*O;
void out(int v,char c)
{
	if(v==-1){ *(O++)='-'; *(O++)='1'; *(O++)=c; return ; }
	static int s[N],t; t=0;
	while(v){ s[++t]=v%10; v/=10; }
	if(!t) s[t=1]=0;
	while(t) *(O++)=s[t--]+48;
	*(O++)=c;
}
int main()
{
	O=Out;
	n=read(); m=read();
	fr(i,0,n) scanf("%s",s[i]);
	fr(i,0,n-1) fr(j,0,m-1)
	{
		if(i!=n-1) Add((i*m+j)*2,((i+1)*m+j)*2);
		if(i) Add((i*m+j)*2+1,((i-1)*m+j)*2+1);
		if(j!=m-1) Add((i*m+j)*2+(s[i][j]=='N'),(i*m+j+1)*2+(s[i][j+1]=='N'));
		if(j) Add((i*m+j)*2+(s[i][j]=='Z'),(i*m+j-1)*2+(s[i][j-1]=='Z'));
	}
	fr(i,0,n*m*2-1) for(auto j:e[i]) d[i]++;
	fr(i,0,n*m*2-1) if(!d[i]) q[++r]=i;
	l=1;
	while(l<=r)
	{
		int u=q[l++];
		for(auto v:E[u])
		{
			d[v]--;
			if(!d[v]) q[++r]=v;
		}
	}
	fr(i,1,r) p[q[i]]=1;
	fr(i,0,n*m*2-1) d[i]=e[i].size();
	fprintf(stderr,"%d\n",clock());
	fr(i,0,n*m-1) ans[i]=M;
	fr(i,0,m-1)
	{
		for(int *p1=vis,*p2=vis+n*m;p1!=p2;) *(p1++)=-1;
		Ans=0;
		fr(j,0,n-1){ dfs(j*m+i,1); ans[j*m+i]=std::min(ans[j*m+i],Ans); }
	}
	fprintf(stderr,"%d\n",clock());
	fr(i,0,m-1)
	{
		for(int *p1=vis,*p2=vis+n*m;p1!=p2;) *(p1++)=-1;
		Ans=0;
		fd(j,n-1,0){ dfs(j*m+i,0); ans[j*m+i]=std::min(ans[j*m+i],Ans); }
	}
	fr(i,0,n*m-1) out(ans[i]==M?-1:ans[i]*2,i%m==m-1?'\n':' ');
	while(O!=Out+(1<<22)) *(O++)=' ';
	fwrite(Out,1<<11,1<<11,stdout);
	fprintf(stderr,"%d\n",clock());
	return 0;
}