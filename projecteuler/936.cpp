#include<bits/stdc++.h>
#define fr(i,a,b) for(int i=(a),end_##i=(b);i<=end_##i;i++)
#define fd(i,a,b) for(int i=(a),end_##i=(b);i>=end_##i;i--)
#define i64 long long
const int N=60;
i64 f[N][N]; i64 F[N][N];
i64 C(int n,int m)
{
	i64 res=1;
	fr(i,1,m) res=res*(n-i+1)/i;
	return res;
}
i64 Q(int n,int m);
i64 q(int n,int m)
{
	if(f[n][m]!=-1) return f[n][m];
	if(n==1) return 1;
	static i64 g[N][N]; memset(g,0,sizeof(g)); g[0][1]=1;
	fr(k,1,n-1) fd(i,m-1,1) fr(l,1,i) fr(j,1,n-k*l) g[i][j+k*l]+=g[i-l][j]*C(Q(k,m)+l-1,l);
	// printf("%lld mod %lld = %lld\n",g[m-1][n],fac[m-1],g[m-1][n]%fac[m-1]);
	// printf("%d %d  %lld\n",n,m,g[m-1][n]);
	return f[n][m]=g[m-1][n];
}
i64 Q(int n,int m)
{
	if(F[n][m]!=-1) return F[n][m];
	i64 ans=0;
	fr(i,1,n) if(i!=m) ans+=q(n,i);
	return F[n][m]=ans;
}
i64 P(int n)
{
	i64 ans=0;
	fr(m,1,n)
	{
		static i64 g[N][N]; memset(g,0,sizeof(g)); g[0][1]=1;
		fr(k,1,(n-1)/2) fd(i,m,1) fr(l,1,i) fr(j,1,n-k*l) g[i][j+k*l]+=g[i-l][j]*C(Q(k,m)+l-1,l);
		// printf("%d %d  %lld\n",n,m,g[m][n]);
		ans+=g[m][n];
	}
	if(n%2==0) fr(i,1,n/2) fr(j,i+1,n/2) ans+=q(n/2,i)*q(n/2,j);
	return ans;
}
int main()
{
	fr(i,0,N-1) fr(j,0,N-1) f[i][j]=F[i][j]=-1;
	int n=50; i64 ans=0; fr(i,3,n) ans+=P(i);
	printf("%lld\n",ans);
	return 0;
}