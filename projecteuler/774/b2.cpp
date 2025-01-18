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
const int N=210,L=35,M=100000,mod=998244353;
int n,m;
i64 ans;
int l;
i64 C[L][L],CC[L][L][L][L];
int Q(int l,int r){ return __builtin_popcount((m&((1<<(r+1))-1))>>l); }
int id[L][L][L][L],Id;
bool v2[N][M][4]; int f2[N][M][4];
i64 dp2(int n,int m,int c1,int c2,int c0,int o)
{
	if(n==2) return m<l||(m==l&&!o)||c0;
	if(m>l) return 0;
	if(v2[n][id[m][c1][c2][c0]][o]) return f2[n][id[m][c1][c2][c0]][o];
	v2[n][id[m][c1][c2][c0]][o]=1; i64 ans=0;
	int flag=0;
//	if(n==4&&m==2&&c1==1&&c2==1&&c0==1&&o==0) flag=1;
	fr(i,2,n-1) fr(j,m,l) if(Q(j,j))
	{
		int C1=c1+Q(m+(o&1),j-1),C2=c2+Q(m+((o>>1)&1),j-1),C0=c0+Q(m+!!o,j-1);
		C1-=C0; C2-=C0; int C3=j-C0-C1-C2;
		fr(v0,0,C0) fr(v1,0,C1) fr(v2,0,C2) fr(v3,0,C3)
		{
			ans=(ans+CC[C0][v0][C1][v1]*CC[C2][v2][C3][v3]%mod*
			dp2(i,j,C0+C1,v0+v1+v2+v3,v0+v1,2+(j==m&&(o&1)))%mod*
			dp2(n-i+1,j+1,C0+C2+(j!=m||!(o&2)),v0+v1+v2+v3,v0+v2,0))%mod;
//			if(flag) printf(" %d %d  %d %d %d %d   %d %d %d %d  %lld\n",i,j,C0,C1,C2,C3,v0,v1,v2,v3,ans);
		}
	}
	if(ans) printf("%d %d  %d %d %d  %d   %lld\n",n,m,c1,c2,c0,o,ans);
	return f2[n][id[m][c1][c2][c0]][o]=ans;
}
bool v1[N][L][2][L]; int f1[N][L][2][L];
i64 dp1(int n,int m,int d,int c)
{
	if(n==1) return 1;
	if(m+d>l) return 0;
	if(v1[n][m][d][c]) return f1[n][m][d][c];
	v1[n][m][d][c]=1; i64 ans=0;
	int flag=0;
//	if((n==3&&m==1&&d==0&&c==1)) flag=1;
//	if((n==2&&m==2&&d==0&&c==1)) flag=1;
	fr(i,2,n) fr(j,m+d,l) if(Q(j,j))
	{
		int c1=c+Q(m+1,j-1),c2=j-c1;
//		if(flag) printf(" %d %d  %d %d\n",i,j,c1,c2);
		fr(x,0,c1) fr(y,0,c2)
		{
			ans=(ans+dp1(n-i+1,j,0,x+y)*dp2(i,j+1,c1+(m!=j),x+y,x,0)%mod*CC[c1][x][c2][y])%mod;
//			if(flag) printf("  %d %d  %d %d   %lld\n",i,j,x,y,ans);
		}
	}
//	if(flag&&ans) printf("%d %d %d %d  %lld\n",n,m,d,c,ans);
	return f1[n][m][d][c]=ans;
}
void solve(int n,int m)
{
	static int f[2000][2000];
	fr(i,0,m) f[1][i]=1;
	fr(i,2,n) fr(j,0,m) fr(k,0,m) if(j&k) f[i][k]=(f[i][k]+f[i-1][j])%mod;
	int ans=0;
	fr(i,0,m) ans=(ans+f[n][i])%mod;
	printf("%d\n",ans);
}
int main()
{
	l=30; fr(i,0,l) fr(j,0,i) fr(k,0,i) fr(o,0,std::min(j,k)) id[i][j][k][o]=++Id;
//	printf("%d\n",Id); return 0;
//	(sizeof(f2)/1024./1024.);
	n=30; fr(i,0,n){ C[i][0]=C[i][i]=1; fr(j,1,i-1) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod; }
	fr(i,0,n) fr(j,0,n) fr(k,0,n) fr(l,0,n) CC[i][j][k][l]=C[i][j]*C[k][l]%mod;
	n=read(); m=read()+1; l=0; while((1<<l)<=m) l++;; l--;
//	solve(n,m-1);
	fr(i,1,n) fr(j,0,l) if(Q(j,j)) fr(k,0,j)
		ans=(ans+dp1(i,j,1,k)*dp1(n-i+1,j,0,k)%mod*C[j][k])%mod;
	printf("%lld\n",ans);
	return 0;
}