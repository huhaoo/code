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
const int N=510;
int a[N][N],d[N][N],n,ans;
int x[N*N],y[N*N];
void dfs(int x,int y,int D)
{
	if(!x||!y||x>n||y>n||d[x][y]<=D) return ;
	d[x][y]=D;
	dfs(x+1,y,d[x][y]+a[x][y]);
	dfs(x-1,y,d[x][y]+a[x][y]);
	dfs(x,y+1,d[x][y]+a[x][y]);
	dfs(x,y-1,d[x][y]+a[x][y]);
}
int main()
{
	n=read();
	fr(i,1,n) fr(j,1,n) a[i][j]=1;
	fr(i,1,n*n)
	{
		int p=read();
		x[i]=(p+n-1)/n; y[i]=(p%n==0?n:p%n);
	}
	fr(i,1,n) fr(j,1,n) d[i][j]=std::min({i-1,j-1,n-i,n-j});
	fr(i,1,n*n)
	{
		int X=x[i],Y=y[i]; a[X][Y]=0;
//		printf("%d %d %d\n",X,Y,d[X][Y]);
		ans+=d[X][Y]; d[X][Y]++; dfs(X,Y,d[X][Y]-1);
//		fr(j,1,n) fr(k,1,n) printf("%d%c",d[j][k],k==n?'\n':' ');
	}
	printf("%d\n",ans);
	return 0;
}