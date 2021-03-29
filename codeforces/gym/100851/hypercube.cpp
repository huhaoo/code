/***************************************************************
	File name: hypercube.cpp
	Author: huhao
	Create time: Sat 24 Oct 2020 02:53:11 PM CST
***************************************************************/
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
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
const int N=10;
int h,n,m;
int a[N][N][N],A;
int x[N][8][4];
int p[N];
int e[N][N];
int vis[N];
int Dfs(int u,int F)
{
	int ans=1; vis[u]=1;
	fr(v,1,8) if(e[u][v]&&v!=F)
	{
		if(vis[v]) return 0;
		ans+=Dfs(v,u);
	}
	return ans;
}
int dfs(int u,int F)
{
	fr(v,1,8) if(e[u][v]&&v!=F)
	{
		int o=e[u][v]-1;
		fr(i,0,7) if(((i>>(o>>1))&1)==(o&1)) fr(j,0,3) x[v][i^(1<<(o>>1))][j]=x[u][i][j];
		fr(i,0,7) if(((i>>(o>>1))&1)==(o&1)) if(x[u][i][p[v]>>1]!=(p[v]&1)) return 0;
		fr(i,0,7) if(((i>>(o>>1))&1)==(o&1))
		{
			fr(j,0,3) x[v][i][j]=x[v][i^(1<<(o>>1))][j];
			x[v][i][p[u]>>1]^=1;
		}
		if(!dfs(v,u)) return 0;
	}
	return 1;
}
int main()
{
	freopen("hypercube.in","r",stdin); freopen("hypercube.out","w",stdout);
	m=read(); n=read(); h=read();
	fr(i,1,h) fr(j,1,n)
	{
		static char s[N]; scanf("%s",s+1);
		fr(k,1,m) if(s[k]=='x') a[i][j][k]=++A;
	}
	fr(i,1,h) fr(j,1,n) fr(k,1,m) if(a[i][j][k])
	{
		if(a[i-1][j][k]) e[a[i][j][k]][a[i-1][j][k]]=1;
		if(a[i+1][j][k]) e[a[i][j][k]][a[i+1][j][k]]=2;
		if(a[i][j-1][k]) e[a[i][j][k]][a[i][j-1][k]]=3;
		if(a[i][j+1][k]) e[a[i][j][k]][a[i][j+1][k]]=4;
		if(a[i][j][k-1]) e[a[i][j][k]][a[i][j][k-1]]=5;
		if(a[i][j][k+1]) e[a[i][j][k]][a[i][j][k+1]]=6;
	}
	if(A!=8){ printf("No\n"); return 0; }
//	fr(i,1,8) fr(j,1,8) printf("%d%c",e[i][j],j==8?'\n':' ');
	fr(i,1,8) p[i]=i-1;
	if(Dfs(1,0)!=8){ printf("No\n"); return 0; }
	do
	{
		fr(i,0,7) fr(j,0,2) x[1][i][j+1]=(i>>j)&1;
		if(dfs(1,0)){ printf("Yes\n"); return 0; }
	}
	while(std::next_permutation(p+2,p+9));
	printf("No\n");
	return 0;
}
