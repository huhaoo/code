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
const int N=310,mod=998244353;
int n,m,l[N*N],r[N*N],R[N][N][N];
int f[N][N][N],vis[N][N][N];
int dp(int l,int r,int p)
{
	if(l>r) return 1;
	if(vis[l][r][p]) return f[l][r][p];
	vis[l][r][p]=1; int &ans=f[l][r][p];
	fr(i,l,p) ans=(ans+(i64)dp(l,i-1,i-1)*dp(i+1,r,R[l][r][i]))%mod;
	return ans;
}
int main()
{
	n=read(); m=read();
	fr(i,1,m){ l[i]=read(); r[i]=read(); }
	fr(i,1,n) fr(j,1,n) fr(k,1,n) R[i][j][k]=k;
	fr(i,1,m) fr(k,l[i],r[i]) R[l[i]][r[i]][k]=r[i];
	fr(k,1,n) fd(i,n,1) fr(j,i,n){ R[i][j][k]=std::max({R[i][j][k],R[i+1][j][k],R[i][j-1][k]}); }
//	fr(i,1,n) printf("%d%c",R[1][n][i],i==n?'\n':' ');
	printf("%d\n",dp(1,n,n));
	return 0;
}