#include<stdio.h>
#include<string.h>
#include<math.h>
#include<algorithm>
#include<vector>
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
		r=(r<<3)+(r<<1)+(c^48);
		c=getchar();
	}
	return r*t;
}
const int N=210,mod=998244353;
int n,f[N][N][2][2][N],p[N],q[N],F[N],ans,m,g[N];
void Add(int &a,int b){ a+=b; if(a>=mod) a-=mod; }
int main()
{
	n=read(); p[0]=p[n+1]=-1; q[0]=q[n+1]=-1;
	fr(i,1,n)
	{
		p[i]=read();
		if(p[i]!=-1) q[p[i]]=i;
		else{ m++; p[i]=0; }
	}
	f[0][0][0][0][0]=1;
	fr(i,0,n) fr(j,0,n) fr(x,0,1) fr(y,0,1)
	{
		if(p[i]&&p[i]==j) continue;
		if(x&&y&&!p[i]&&!q[j]) fd(k,m,0)
		{
			Add(f[i+1][j][1][0][k+1],f[i][j][x][y][k]);
			Add(f[i][j+1][0][1][k+1],f[i][j][x][y][k]);
		}
		fd(k,m,0)
		{
			i64 v=f[i][j][x][y][k];
			Add(f[i+1][j][1][y][k],v);
			Add(f[i][j+1][x][1][k],v);
		}
	}
//	fr(i,0,n+1) fr(j,0,n+1) printf("%d%c",f[i][j][1][1][0],j==n+1?'\n':' ');
	g[0]=1; fr(i,1,m) g[i]=(i64)g[i-1]*i%mod;
	fr(i,0,n) fr(j,0,1) fr(k,0,1) fr(l,0,m) Add(F[l],(i64)(f[n+1][i][j][k][l]+f[i][n+1][j][k][l])*g[m-l]%mod);
//	fr(i,0,m) printf("%d%c",F[i],i==m?'\n':' ');
	fr(l,0,m) Add(ans,(l&1?mod-F[l]:F[l]));
	printf("%d\n",ans);
	return 0;
}