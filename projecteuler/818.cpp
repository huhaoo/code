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
i64 cnt[20];
int Cnt;
int v[100];
i64 C[100][20],ans;
const int A[5]={0,1,14,36,24};
int n,m,k;
int a[100][4];
int b[100000][3];
void dfs(int u,int t)
{
	if(!u){ cnt[Cnt]++; return; }
	fr(i,u,t)
	{
		fr(j,0,2) Cnt+=((v[b[i][j]]++)==0);
		dfs(u-1,i-1);
		fr(j,0,2) Cnt-=((--v[b[i][j]])==0);
	}
}
int main()
{
	fr(x,1,3) fr(y,1,3) fr(z,1,3) fr(w,1,3){ n++; a[n][0]=x; a[n][1]=y; a[n][2]=z; a[n][3]=w; }
	fr(i,1,n) fr(j,i+1,n) fr(k,j+1,n)
	{
		int flag=1;
		fr(l,0,3){ if(a[i][l]==a[j][l]&&a[j][l]==a[k][l]) continue; if(a[i][l]!=a[j][l]&&a[i][l]!=a[k][l]&&a[j][l]!=a[k][l]) continue; flag=0; }
		if(flag){ ::k++; b[::k][0]=i; b[::k][1]=j; b[::k][2]=k; }
	}
	m=12;
	fr(i,0,n)
	{
		C[i][0]=1;
		fr(j,1,m) C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	fr(i,1,4)
	{
		memset(cnt,0,sizeof(cnt));
		dfs(i,k);
		fr(j,0,i*3) printf("%I64d%c",cnt[j],j==end_j?'\n':' '); fflush(stdout);
		fr(j,0,m) ans+=A[i]*cnt[j]*C[n-j][m-j];
	}
	printf("%lld\n",ans);
	return 0;
}